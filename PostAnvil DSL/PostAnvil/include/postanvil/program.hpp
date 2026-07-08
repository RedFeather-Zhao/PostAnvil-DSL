/**
 * @file   program.hpp
 * @brief  PostAnvil 编译结果，管理算子管道并执行评估
 *
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include "operators.hpp"
#include <vector>
#include <memory>
#include <unordered_map>
#include <tuple>

namespace postanvil {

/**
 * @brief 编译后的程序，包含算子管道和函数表
 * @details 由编译器生成，可反复应用于不同场景
 *          支持导入变量预设和导出值获取
 */
class CompiledProgram {
public:
	CompiledProgram() = default;
	CompiledProgram(const CompiledProgram&) = delete;
	CompiledProgram(CompiledProgram&&) = default;
	CompiledProgram& operator=(const CompiledProgram&) = delete;
	CompiledProgram& operator=(CompiledProgram&&) = default;

	/**
	 * @brief 对输入场景执行编译后的程序
	 * @param scene 输入场景
	 * @return EvalResult 评估结果，包含变换后的场景
	 */
	EvalResult evaluate(const Scene& scene) const {
		EvaluationContext ctx(scene);
		ctx.functions = functions;

		for (const auto& op : operators) {
			op->apply(ctx);
		}

		return ctx.to_result();
	}

	/**
	 * @brief 从评估结果中获取导出的值
	 * @param host_name 宿主端变量名
	 * @param result 评估结果
	 * @return Val 导出的值
	 * @throws RuntimeError 导出值不存在时抛出
	 */
	Val get_exported(const std::string& host_name, const EvalResult& result) const {
		std::string key = "__export__" + host_name;
		if (auto it = result.kept.variables.find(key); it != result.kept.variables.end()) {
			return it->second;
		}
		throw RuntimeError("Exported value '" + host_name + "' not found");
	}

	/**
	 * @brief 为场景预设导入变量
	 * @param scene 待修改的场景
	 * @param local_name 本地变量名
	 * @param value 导入值
	 */
	void set_import(Scene& scene, const std::string& local_name, Val const& value) const {
		scene.variables[local_name] = value;
	}

	std::vector<std::unique_ptr<SceneOperator>> operators; // 算子执行序列
	std::unordered_map<std::string, CompiledFunc> functions; // 函数注册表

	std::vector<std::tuple<std::string, std::string, Type>> imports; // 导入声明：宿主名、本地名、类型
	std::vector<std::tuple<ValFunc, std::string>> exports;           // 导出声明：表达式、宿主名
};

} // namespace postanvil

