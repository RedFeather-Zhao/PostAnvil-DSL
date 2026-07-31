#pragma once

#include "pch.h"

namespace postanvil::test {

using ExpectedCount = std::pair<std::string_view, std::size_t>;

/** @brief 使用简短实例列表构造默认 200x200 场景。 */
Scene make_scene(
	std::initializer_list<Instance> instances,
	Image image = { 200, 200 });

/** @brief 快速构造同一类别、相同检测框尺寸、不同置信度的场景。 */
Scene make_confidence_scene(
	std::string_view class_name,
	std::initializer_list<double> confidences,
	double width = 10,
	double height = 10,
	Image image = { 200, 200 });

/** @brief 编译 DSL 并在给定场景上执行。 */
Scene evaluate(std::string_view source, Scene input);

/** @brief 执行 DSL，并集中验证一个或多个类别的实例数量。 */
Scene evaluate_and_expect_counts(
	std::string_view source,
	Scene input,
	std::initializer_list<ExpectedCount> expected_counts);

std::size_t count(const Scene& scene, std::string_view class_name);
const Instance& instance_at(
	const Scene& scene,
	std::string_view class_name,
	std::size_t zero_based_index = 0);

void expect_count(
	const Scene& scene,
	std::string_view class_name,
	std::size_t expected);

void expect_num_prop(
	const Scene& scene,
	std::string_view class_name,
	std::size_t zero_based_index,
	std::string_view property,
	double expected,
	double tolerance = 1e-9);

void expect_bool_prop(
	const Scene& scene,
	std::string_view class_name,
	std::size_t zero_based_index,
	std::string_view property,
	bool expected);

void expect_str_prop(
	const Scene& scene,
	std::string_view class_name,
	std::size_t zero_based_index,
	std::string_view property,
	std::string_view expected);

void expect_class_num(
	const Scene& scene,
	std::string_view class_name,
	std::string_view property,
	double expected,
	double tolerance = 1e-9);

void expect_class_bool(
	const Scene& scene,
	std::string_view class_name,
	std::string_view property,
	bool expected);

void expect_export_num(
	const Scene& scene,
	std::string_view name,
	double expected,
	double tolerance = 1e-9);

} // namespace postanvil::test
