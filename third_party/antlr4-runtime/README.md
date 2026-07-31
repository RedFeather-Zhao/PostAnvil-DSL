# ANTLR4 C++ Runtime

本目录内嵌 ANTLR4 C++ Runtime 4.13.2 的 `runtime/src`，来源归档为：
`tools/antlr/antlr4-cpp-runtime-4.13.2-source.zip`。

上游链接：`https://github.com/antlr/antlr4/tree/dev/runtime/Cpp`

本地可移植性修补：

- `src/atn/ProfilingATNSimulator.cpp` 显式包含 `<chrono>`，避免新版 MSVC
  不再提供间接包含时编译失败。

上游许可证见 `../licenses/ANTLR4.txt`。
