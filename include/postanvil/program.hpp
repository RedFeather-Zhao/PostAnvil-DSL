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
	 * @return Scene 评估结果场景
	 */
	Scene evaluate(const Scene& scene) const {
		EvaluationContext ctx(scene);
		ctx.functions = functions;

		for (size_t i = 0; i < operators.size(); i++) {
			auto& op = operators[i];
			try {
				op->apply(ctx);
			}
			catch (const RuntimeError& e) {
				// 错误包装，定位到算子，未来可支持定位到具体行
				throw RuntimeError(e.what(),
					static_cast<int>(i),
					operation_kind_to_string(op->kind));
			}
		}

		return ctx.to_result();
	}

	std::vector<std::unique_ptr<SceneOperator>> operators;	// 算子执行序列
	detail::str_map<FunctionInfo> functions;				// 函数注册表
};

} // namespace postanvil

