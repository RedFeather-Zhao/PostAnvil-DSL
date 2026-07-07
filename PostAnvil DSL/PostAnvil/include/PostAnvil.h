/**
 * @file PostAnvil.h
 * @brief PostAnvil 统一包含头。此头文件对外暴露 PostAnvil 库的主要接口，
 *        方便用户仅包含一个头文件即可使用 ANTLR4 解析器、编译器与上下文类型。
 *
 * 使用方法：
 * @code
 * #include "PostAnvil.h"
 * using namespace postanvil;
 * @endcode
 */
#pragma once

#include "postanvil/detail.hpp"
#include "postanvil/utils.hpp"
#include "postanvil/error.hpp"
#include "postanvil/type.hpp"

#include "postanvil/instance.hpp"
#include "postanvil/scene.hpp"

#include "postanvil/operators.hpp"
#include "postanvil/program.hpp"
#include "postanvil/expr_compiler.hpp"
#include "postanvil/compiler.hpp"

