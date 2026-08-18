#include "pch.h"
#include "TestSupport.hpp"

using Microsoft::VisualStudio::CppUnitTestFramework::Assert;

namespace postanvil::test {

namespace {

void add_instance(Scene& scene, std::string_view cls_name, Instance instance)
{
	const auto handle = scene.inst_add(std::move(instance));
	scene.cls_add_inst(cls_name, handle.id);
}

} // namespace

LabeledInstance make_instance(
	std::string_view cls_name,
	double x,
	double y,
	double width,
	double height,
	double confidence)
{
	return {
		std::string(cls_name),
		Instance(x, y, width, height, confidence)
	};
}

Scene make_scene(std::initializer_list<LabeledInstance> instances, Image image)
{
	Scene scene(std::move(image));
	for (const auto& input : instances) {
		add_instance(scene, input.cls_name, input.instance);
	}
	return scene;
}

Scene make_confidence_scene(
	std::string_view cls_name,
	std::initializer_list<double> confidences,
	double width,
	double height,
	Image image)
{
	Scene scene(image);
	for (const double confidence : confidences) {
		add_instance(scene, cls_name, Instance(0, 0, width, height, confidence));
	}
	return scene;
}

Scene evaluate(std::string_view source, Scene input)
{
	Compiler compiler;
	auto program = compiler.compile(std::string(source));
	return program.evaluate(input);
}

Scene evaluate_and_expect_counts(std::string_view source,
								 Scene input,
								 std::initializer_list<ExpectedCount> expected_counts)
{
	auto output = evaluate(source, std::move(input));
	for (const auto& [cls_name, expected] : expected_counts) {
		expect_count(output, cls_name, expected);
	}
	return output;
}

std::size_t count(const Scene& scene, std::string_view cls_name)
{
	return scene.cls_inst_count(cls_name);
}

const Instance& instance_at(
	const Scene& scene,
	std::string_view cls_name,
	std::size_t zero_based_index)
{
	const auto& ids = scene.cls_insts(cls_name);
	Assert::IsTrue(zero_based_index < ids.size(), L"实例索引越界");
	return scene.inst_at(ids[zero_based_index]);
}

void expect_count(
	const Scene& scene,
	std::string_view cls_name,
	std::size_t expected)
{
	Assert::AreEqual(expected, count(scene, cls_name), L"类别实例数量不匹配");
}

void expect_num_prop(
	const Scene& scene,
	std::string_view cls_name,
	std::size_t zero_based_index,
	std::string_view property,
	double expected,
	double tolerance)
{
	const auto actual = instance_at(scene, cls_name, zero_based_index)
		.get_prop(std::string(property)).as_num();
	Assert::AreEqual(expected, actual, tolerance, L"实例数值属性不匹配");
}

void expect_bool_prop(
	const Scene& scene,
	std::string_view cls_name,
	std::size_t zero_based_index,
	std::string_view property,
	bool expected)
{
	const auto actual = instance_at(scene, cls_name, zero_based_index)
		.get_prop(std::string(property)).as_bool();
	Assert::AreEqual(expected, actual, L"实例布尔属性不匹配");
}

void expect_str_prop(
	const Scene& scene,
	std::string_view cls_name,
	std::size_t zero_based_index,
	std::string_view property,
	std::string_view expected)
{
	const auto actual = instance_at(scene, cls_name, zero_based_index)
		.get_prop(std::string(property)).as_str();
	Assert::AreEqual(std::string(expected), actual, L"实例字符串属性不匹配");
}

void expect_class_num(
	const Scene& scene,
	std::string_view cls_name,
	std::string_view property,
	double expected,
	double tolerance)
{
	const auto actual = scene.cls_prop(cls_name, property).as_num();
	Assert::AreEqual(expected, actual, tolerance, L"类别数值属性不匹配");
}

void expect_class_bool(
	const Scene& scene,
	std::string_view cls_name,
	std::string_view property,
	bool expected)
{
	const auto actual = scene.cls_prop(cls_name, property).as_bool();
	Assert::AreEqual(expected, actual, L"类别布尔属性不匹配");
}

void expect_export_num(
	const Scene& scene,
	std::string_view name,
	double expected,
	double tolerance)
{
	const auto actual = scene.io_export(name).as_num();
	Assert::AreEqual(expected, actual, tolerance, L"导出数值不匹配");
}

} // namespace postanvil::test
