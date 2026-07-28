#include "test_common.hpp"

bool check_count(
    const Scene& res,
    const std::string& cls,
    int expected_count)
{
    auto it = res.objects.find(cls);
    int actual = 0;
    if (it != res.objects.end()) {
        actual = static_cast<int>(it->second.size());
    }
    return actual == expected_count;
}

bool check_prop(
    const Scene& res,
    const std::string& cls,
    int idx,
    const std::string& prop,
    const Val& expected)
{
    auto it = res.objects.find(cls);
    if (it == res.objects.end() || idx >= static_cast<int>(it->second.size())) {
        return false;
    }

    Val actual = it->second[idx].get_prop(prop);
    if (!type_strict_equal(actual.type(), expected.type())) {
        return false;
    }
    return actual == expected;
}

bool check_class_prop(
    const Scene& res,
    const std::string& cls,
    const std::string& prop,
    const Val& expected)
{
    auto it = res.class_props.find(cls);
    if (it == res.class_props.end()) {
        return false;
    }

    auto pit = it->second.find(prop);
    if (pit == it->second.end()) {
        return false;
    }
    return pit->second == expected;
}

bool run_test_case(
    const TestCase& tc,
    PostAnvilCompiler& compiler)
{
    try {
        CompiledProgram prog = compiler.compile(tc.source);
        Scene scene = tc.buildScene();
        Scene res = prog.evaluate(scene);

        std::string err_msg;
        bool ok = tc.verify(res, err_msg);

        if (ok) {
            std::cout << "  [PASS] " << tc.name;
        }
        else {
            std::cout << "  [FAIL] " << tc.name;
        }

        if (!ok && !err_msg.empty()) {
            std::cout << "  (" << err_msg << ")";
        }
        std::cout << std::endl;
        return ok;
    }
    catch (const std::exception& e) {
        std::cout << "  [FAIL] " << tc.name << "  (exception: " << e.what() << ")" << std::endl;
        return false;
    }
}
