#pragma once

// 单元测试框架与 PostAnvil/ANTLR 头文件解析开销较大，统一放入预编译头。
// 这里只放稳定且被绝大多数测试源文件共同使用的头文件。
#include "CppUnitTest.h"
#include <PostAnvil.h>

#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
