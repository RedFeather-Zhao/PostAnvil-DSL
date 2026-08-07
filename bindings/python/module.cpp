#include <PostAnvil.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>
#include <utility>

namespace py = pybind11;
using namespace postanvil;

namespace {

Val from_python(const py::handle& value)
{
    if (py::isinstance<py::bool_>(value)) return value.cast<bool>();
    if (py::isinstance<py::int_>(value) || py::isinstance<py::float_>(value)) {
        return value.cast<double>();
    }
    if (py::isinstance<py::str>(value)) return value.cast<std::string>();
    if (py::isinstance<Instance>(value)) return value.cast<Instance>();
    throw py::type_error("PostAnvil values support bool, number, str, or Instance");
}

py::object to_python(const Val& value)
{
    switch (value.type()) {
    case Type::T_NUM:  return py::float_(value.as_num());
    case Type::T_STR:  return py::str(value.as_str());
    case Type::T_BOOL: return py::bool_(value.as_bool());
    case Type::T_INST: return py::cast(*value.as_inst());
    default: throw PARuntimeError("Cannot convert an invalid PostAnvil value to Python");
    }
}

} // namespace

PYBIND11_MODULE(_postanvil, module)
{
    module.doc() = "PostAnvil DSL native bindings";
    module.attr("__version__") = version();

    py::register_exception<PAParseError>(module, "PAParseError", PyExc_RuntimeError);
    py::register_exception<PACompileError>(module, "PACompileError", PyExc_RuntimeError);
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
        .def(py::init<std::string_view, double, double, double, double, double>(),
             py::arg("class_name"), py::arg("x"), py::arg("y"),
             py::arg("width"), py::arg("height"), py::arg("confidence"))
        .def_property("x", &Instance::x1, &Instance::set_x1)
        .def_property("y", &Instance::y1, &Instance::set_y1)
        .def_property("width", &Instance::w, &Instance::set_w)
        .def_property("height", &Instance::h, &Instance::set_h)
        .def_property("confidence", &Instance::conf, &Instance::set_conf)
        .def_property("class_name", &Instance::cls, &Instance::set_cls)
        .def_property_readonly("id", &Instance::id)
        .def_property_readonly("index", &Instance::index)
        .def_property_readonly("x2", &Instance::x2)
        .def_property_readonly("y2", &Instance::y2)
        .def_property_readonly("area", &Instance::area)
        .def("set_property", [](Instance& self, const std::string& name,
                                const py::handle& value) {
            self.set_prop(name, from_python(value));
        })
        .def("get_property", [](const Instance& self, const std::string& name) {
            return to_python(self.get_prop(name));
        });

    py::class_<Scene>(module, "Scene")
        .def(py::init<const Image&, const Instances&>(),
             py::arg("image"), py::arg("instances") = Instances{})
        .def_readwrite("image", &Scene::image)
        .def("add", py::overload_cast<const Instance&>(&Scene::add),
             py::return_value_policy::reference_internal)
        .def("count", [](const Scene& self, const std::string& class_name) {
            const auto it = self.objects.find(class_name);
            return it == self.objects.end() ? std::size_t{0} : it->second.size();
        })
        .def("instances", [](const Scene& self, const std::string& class_name) {
            const auto it = self.objects.find(class_name);
            return it == self.objects.end() ? Instances{} : it->second;
        })
        .def("class_names", [](const Scene& self) {
            std::vector<std::string> names;
            names.reserve(self.objects.size());
            for (const auto& [name, _] : self.objects) {
                names.push_back(name);
            }
            return names;
        })
        .def("add_import", [](Scene& self, const std::string& name,
                              const py::handle& value) -> Scene& {
            return self.add_import(name, from_python(value));
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
