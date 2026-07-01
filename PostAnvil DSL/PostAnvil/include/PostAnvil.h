/**
 * @file PostAnvil.h
 * @brief PostAnvil 统一包含头。此头文件对外暴露 PostAnvil 库的主要接口，
 *        方便用户仅包含一个头文件即可使用解析器、词法器、AST、求值器与上下文类型。
 *
 * 使用方法：
 * @code
 * #include "PostAnvil.h"
 * using namespace postanvil;
 * @endcode
 */
#pragma once

#include "postanvil/ast.hpp"
#include "postanvil/lexer.hpp"
#include "postanvil/parser.hpp"
#include "postanvil/context.hpp"
#include "postanvil/compiler.hpp"
