#include <PostAnvil.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <algorithm>
#include <cctype>
#include <exception>
#include <format>
#include <string>
#include <utility>

namespace py = pybind11;
using namespace postanvil;

namespace {

PyObject* g_compile_error_type = nullptr;

std::string normalize_name(std::string name)
{
    for (auto& ch : name) {
        ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
    }
    return name;
}

Val from_python(const py::handle& value)
{
    if (py::isinstance<py::bool_>(value)) return value.cast<bool>();
    if (py::isinstance<py::int_>(value) || py::isinstance<py::float_>(value)) {
        return value.cast<double>();
    }
    if (py::isinstance<py::str>(value)) return value.cast<std::string>();
    if (py::isinstance<InstanceHandle>(value)) return value.cast<InstanceHandle>();
    throw py::type_error(
        "PostAnvil values support bool, number, str, or InstanceHandle");
}

py::object to_python(const Val& value)
{
    switch (value.type()) {
    case Type::T_NUM:  return py::float_(value.as_num());
    case Type::T_STR:  return py::str(value.as_str());
    case Type::T_BOOL: return py::bool_(value.as_bool());
    case Type::T_INST: return py::cast(value.as_inst());
    default: throw PARuntimeError("Cannot convert an invalid PostAnvil value to Python");
    }
}

void translate_compile_error(std::exception_ptr exception)
{
    if (!exception || g_compile_error_type == nullptr) return;

    try {
        std::rethrow_exception(exception);
    }
    catch (const PACompileError& error) {
        try {
            auto instance = py::reinterpret_steal<py::object>(
                PyObject_CallFunction(g_compile_error_type, "s", error.what()));
            if (!instance) return;

            instance.attr("kind") = py::cast(error.kind());
            instance.attr("message") = py::str(error.message());
            instance.attr("line") = py::int_(error.line());
            instance.attr("column") = py::int_(error.column());
            instance.attr("hint") = py::str(error.hint());
            instance.attr("raw_message") = py::str(error.raw_message());
            if (error.has_source_line()) {
                instance.attr("source_line") = py::str(error.source_line());
            }
            else {
                instance.attr("source_line") = py::none();
            }
            PyErr_SetObject(g_compile_error_type, instance.ptr());
        }
        catch (py::error_already_set& python_error) {
            python_error.restore();
        }
    }
}

} // namespace

PYBIND11_MODULE(_postanvil, module)
{
    module.doc() = "PostAnvil DSL native bindings";
    module.attr("__version__") = version();

    py::enum_<PACompileError::Kind>(module, "CompileErrorKind")
        .value("SYNTAX", PACompileError::Kind::Syntax)
        .value("SEMANTIC", PACompileError::Kind::Semantic)
        .value("INTERNAL", PACompileError::Kind::Internal);

    auto compile_error_type = py::reinterpret_steal<py::object>(
        PyErr_NewException("postanvil.PACompileError", PyExc_RuntimeError, nullptr));
    if (!compile_error_type) throw py::error_already_set();
    module.add_object("PACompileError", compile_error_type);
    g_compile_error_type = compile_error_type.ptr();
    py::register_local_exception_translator(translate_compile_error);

    py::register_exception<PAParseError>(module, "PAParseError", PyExc_RuntimeError);
    py::register_exception<PARuntimeError>(module, "PARuntimeError", PyExc_RuntimeError);

    py::class_<Image>(module, "Image")
        .def(py::init<double, double, std::string>(),
             py::arg("width"), py::arg("height"), py::arg("path") = "")
        .def_readwrite("width", &Image::width)
        .def_readwrite("height", &Image::height)
        .def_readwrite("path", &Image::path)
        .def_property_readonly("area", &Image::area)
        .def_property_readonly("aspect", &Image::aspect);

    py::class_<Instance>(module, "Instance")
        .def(py::init<double, double, double, double, double>(),
             py::arg("x"), py::arg("y"),
             py::arg("width"), py::arg("height"), py::arg("confidence"))
        .def_property("x", &Instance::x1, &Instance::set_x1)
        .def_property("y", &Instance::y1, &Instance::set_y1)
        .def_property("width", &Instance::w, &Instance::set_w)
        .def_property("height", &Instance::h, &Instance::set_h)
        .def_property("confidence", &Instance::conf, &Instance::set_conf)
        .def_property_readonly("id", &Instance::id)
        .def_property_readonly("x2", &Instance::x2)
        .def_property_readonly("y2", &Instance::y2)
        .def_property_readonly("area", &Instance::area)
        .def("set_property", [](Instance& self, std::string name,
                                const py::handle& value) {
            self.set_prop(normalize_name(std::move(name)), from_python(value));
        })
        .def("get_property", [](const Instance& self, std::string name) {
            return to_python(self.get_prop(normalize_name(std::move(name))));
        })
        .def("delete_property", [](Instance& self, std::string name) {
            self.del_prop(normalize_name(std::move(name)));
        });

    py::class_<InstanceHandle>(module, "InstanceHandle")
        .def_property_readonly("id", [](const InstanceHandle& self) {
            return self.id;
        })
        .def_property_readonly("cls_name", [](const InstanceHandle& self) -> py::object {
            if (!self.cls_name.has_value()) return py::none();
            return py::str(*self.cls_name);
        })
        .def("__bool__", [](const InstanceHandle& self) {
            return static_cast<bool>(self);
        })
        .def("__eq__", [](const InstanceHandle& self, const InstanceHandle& other) {
            return self == other;
        })
        .def("__repr__", [](const InstanceHandle& self) {
            return self.cls_name.has_value()
                ? std::format("InstanceHandle(id={}, cls_name='{}')", self.id, *self.cls_name)
                : std::format("InstanceHandle(id={}, cls_name=None)", self.id);
        });

    py::class_<Scene>(module, "Scene")
        .def(py::init<Image>(), py::arg("image"))
        .def_readwrite("image", &Scene::image)
        .def_property_readonly("instance_count", &Scene::inst_count)
        .def("add", [](Scene& self, const std::string& cls_name,
                       const Instance& instance) {
            return self.add(cls_name, instance);
        }, py::arg("cls_name"), py::arg("instance"))
        .def("ensure_class", &Scene::ensure_class, py::arg("cls_name"))
        .def("append_to_class", [](Scene& self, const std::string& cls_name,
                                   const InstanceHandle& handle) {
            return self.append_to_class(cls_name, handle.id);
        }, py::arg("cls_name"), py::arg("handle"))
        .def("append_id_to_class", &Scene::append_to_class,
             py::arg("cls_name"), py::arg("id"))
        .def("replace_class_ids", &Scene::replace_class,
             py::arg("cls_name"), py::arg("ids"))
        .def("count", [](const Scene& self, const std::string& cls_name) {
            return self.get_inst_count(cls_name);
        })
        .def("instance", [](Scene& self, InstanceId id) -> Instance& {
            return self.inst(id);
        }, py::return_value_policy::reference_internal)
        .def("instance_ids", [](const Scene& self, const std::string& cls_name) {
            if (self.get_inst_count(cls_name) == 0) return Scene::InstanceIds{};
            return self.get_inst_ids(cls_name);
        })
        .def("instances", [](Scene& self, const std::string& cls_name) {
            py::list instances;
            if (self.get_inst_count(cls_name) == 0) return instances;

            const auto owner = py::cast(&self, py::return_value_policy::reference);
            for (const auto id : self.get_inst_ids(cls_name)) {
                instances.append(py::cast(
                    &self.inst(id), py::return_value_policy::reference_internal, owner));
            }
            return instances;
        })
        .def("handles", [](const Scene& self, const std::string& cls_name) {
            std::vector<InstanceHandle> handles;
            const auto count = self.get_inst_count(cls_name);
            handles.reserve(count);
            for (std::size_t index = 1; index <= count; ++index) {
                handles.emplace_back(self.get_inst_by_index(
                    cls_name, static_cast<double>(index)));
            }
            return handles;
        })
        .def("class_names", [](const Scene& self) {
            std::vector<std::string> names;
            names.reserve(self.class_index().size());
            for (const auto& [cls_name, _] : self.class_index()) {
                names.emplace_back(cls_name);
            }
            std::ranges::sort(names);
            return names;
        })
        .def("get_by_id", &Scene::get_inst_by_id, py::arg("id"))
        .def("get_by_index", &Scene::get_inst_by_index,
             py::arg("cls_name"), py::arg("index"))
        .def("get_instance_property", [](const Scene& self,
                                         const InstanceHandle& handle,
                                         std::string name) {
            return to_python(self.get_inst_prop(
                handle, normalize_name(std::move(name))));
        })
        .def("set_instance_property", [](Scene& self,
                                         const InstanceHandle& handle,
                                         std::string name,
                                         const py::handle& value) {
            self.set_inst_prop(
                handle, normalize_name(std::move(name)), from_python(value));
        })
        .def("get_class_property", [](const Scene& self,
                                      const std::string& cls_name,
                                      std::string name) {
            return to_python(self.get_cls_prop(
                cls_name, normalize_name(std::move(name))));
        })
        .def("add_import", [](Scene& self, std::string name,
                              const py::handle& value) -> Scene& {
            return self.add_import(
                normalize_name(std::move(name)), from_python(value));
        }, py::return_value_policy::reference_internal)
        .def("get_export", [](const Scene& self, const std::string& name) {
            return to_python(self.get_export(name));
        });

    py::class_<Program>(module, "Program")
        .def("evaluate", &Program::evaluate);

    py::class_<Compiler>(module, "Compiler")
        .def(py::init<>())
        .def("compile", &Compiler::compile);

    module.def("compile", [](const std::string& source) {
        return Compiler{}.compile(source);
    });
}
