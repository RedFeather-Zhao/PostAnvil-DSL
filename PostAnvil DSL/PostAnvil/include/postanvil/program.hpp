/**
 * @file   program.hpp
 * @brief  PostAnvil 编译后的程序 —— CompiledProgram
 * @detail CompiledProgram 是 PostAnvilCompiler 的编译产物，内部持有
 *         一系列算子（SceneOperator），按序对输入场景执行变换。
 *         它可以安全地移动、存储，并反复对不同的场景数据执行相同评估。
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include "postanvil/operators.hpp"
#include <vector>
#include <memory>

namespace postanvil {

// ========================== Program ===========================

/**
 * @brief 编译后的场景规则程序（CompiledProgram）
 *
 * CompiledProgram 是 PostAnvilCompiler 的编译产物，内部持有
 * 一系列算子（SceneOperator），按序对输入场景执行变换。
 *
 * 它可以安全地移动、存储，并反复对不同的场景数据执行相同评估。
 *
 * 使用方式：
 * @code
 *   PostAnvilCompiler compiler;
 *   CompiledProgram program = compiler.compile(source);
 *   EvalResult result = program.evaluate(scene, image);
 * @endcode
 */
class CompiledProgram {
public:
	CompiledProgram() = default;
	CompiledProgram(const CompiledProgram&)				= delete;
	CompiledProgram(CompiledProgram&&)					= default;
	CompiledProgram& operator=(const CompiledProgram&)	= delete;
	CompiledProgram& operator=(CompiledProgram&&)		= default;

	/**
	 * @brief 对场景执行所有算子，返回最终结果
	 *
	 * 执行流程：
	 * 1. 拷贝输入场景，构造 EvaluationContext
	 * 2. 按序执行每个算子的 apply() 方法
	 * 3. 将最终上下文转换为 EvalResult 返回
	 *
	 * @param scene 输入场景数据
	 * @return 评估结果
	 */
	EvalResult evaluate(const Scene& scene) const {
		EvaluationContext ctx(scene);

		for (const auto& op : operators) {
			op->apply(ctx);
		}

		return ctx.to_result();
	}

	/**
	 * @brief 算子序列，按顺序执行以变换场景
	 */
	std::vector<std::unique_ptr<SceneOperator>> operators;
};

} // namespace postanvil