#pragma once

// 公共且稳定的依赖集中放入预编译头，缩短 49 个测试的重复解析时间。
#include "TestFramework.hpp"
#include <PostAnvil.h>

#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
