#include "pch.h"
#include "TestSupport.hpp"

using Microsoft::VisualStudio::CppUnitTestFramework::Assert;

namespace postanvil::test {

Scene make_scene(std::initializer_list<Instance> instances, Image image)
{
	return Scene(image, Instances(instances));
}

Scene make_confidence_scene(
	std::string_view class_name,
	std::initializer_list<double> confidences,
	double width,
	double height,
	Image image)
{
	Scene scene(image);
	for (const double confidence : confidences) {
		scene.add(Instance(class_name, 0, 0, width, height, confidence));
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
	for (const auto& [class_name, expected] : expected_counts) {
		expect_count(output, class_name, expected);
	}
	return output;
}

std::size_t count(const Scene& scene, std::string_view class_name)
{
	const auto it = scene.objects.find(std::string(class_name));
	return it == scene.objects.end() ? 0 : it->second.size();
}

const Instance& instance_at(
	const Scene& scene,
	std::string_view class_name,
	std::size_t zero_based_index)
{
	const auto it = scene.objects.find(std::string(class_name));
	Assert::IsTrue(it != scene.objects.end(), L"类别不存在");
	Assert::IsTrue(zero_based_index < it->second.size(), L"实例索引越界");
	return it->second[zero_based_index];
}

void expect_count(
	const Scene& scene,
	std::string_view class_name,
	std::size_t expected)
{
	Assert::AreEqual(expected, count(scene, class_name), L"类别实例数量不匹配");
}

void expect_num_prop(
	const Scene& scene,
	std::string_view class_name,
	std::size_t zero_based_index,
	std::string_view property,
	double expected,
	double tolerance)
{
	const auto actual = instance_at(scene, class_name, zero_based_index)
		.get_prop(std::string(property)).as_num();
	Assert::AreEqual(expected, actual, tolerance, L"实例数值属性不匹配");
}

void expect_bool_prop(
	const Scene& scene,
	std::string_view class_name,
	std::size_t zero_based_index,
	std::string_view property,
	bool expected)
{
	const auto actual = instance_at(scene, class_name, zero_based_index)
		.get_prop(std::string(property)).as_bool();
	Assert::AreEqual(expected, actual, L"实例布尔属性不匹配");
}

void expect_str_prop(
	const Scene& scene,
	std::string_view class_name,
	std::size_t zero_based_index,
	std::string_view property,
	std::string_view expected)
{
	const auto actual = instance_at(scene, class_name, zero_based_index)
		.get_prop(std::string(property)).as_str();
	Assert::AreEqual(std::string(expected), actual, L"实例字符串属性不匹配");
}

void expect_class_num(
	const Scene& scene,
	std::string_view class_name,
	std::string_view property,
	double expected,
	double tolerance)
{
	const auto& actual = scene.class_props.at(std::string(class_name))
		.at(std::string(property));
	Assert::AreEqual(expected, actual.as_num(), tolerance, L"类别数值属性不匹配");
}

void expect_class_bool(
	const Scene& scene,
	std::string_view class_name,
	std::string_view property,
	bool expected)
{
	const auto& actual = scene.class_props.at(std::string(class_name))
		.at(std::string(property));
	Assert::AreEqual(expected, actual.as_bool(), L"类别布尔属性不匹配");
}

void expect_export_num(
	const Scene& scene,
	std::string_view name,
	double expected,
	double tolerance)
{
	const auto actual = scene.get_export(std::string(name)).as_num();
	Assert::AreEqual(expected, actual, tolerance, L"导出数值不匹配");
}

} // namespace postanvil::test
