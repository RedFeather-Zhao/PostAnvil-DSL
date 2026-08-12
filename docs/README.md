# PostAnvil 文档中心

[返回项目首页](../README.md)

这里是 PostAnvil 文档的统一入口。文档按照读者目标拆分，不需要从头读到尾；找到你
当前要完成的任务，点击对应条目即可。

## 第一次了解项目

- [项目首页与最小示例](../README.md)：先了解 PostAnvil 解决什么问题。
- [DSL 快速开始](dsl/README.md)：用一条规则完成第一次筛选。
- [技术流程图](assets/postanvil-technical-flow.png)：面向非技术读者的整体流程。

## DSL 语言手册

建议按以下顺序阅读：

1. [快速开始与执行顺序](dsl/README.md)
2. [声明与规则](dsl/language.md)
3. [控制流、表达式与类型](dsl/control-flow.md)
4. [属性、内置函数与排序参考](dsl/reference.md)
5. [编译诊断与常见问题](dsl/diagnostics.md)

## 宿主接入

- [C++ 接入](integration/cpp.md)：链接库、创建 Scene、编译并执行规则。
- [Python 接入](integration/python.md)：Python API、实例句柄和 Ultralytics YOLO。
- [Android 接入](integration/android.md)：静态库、JNI、双 ABI 构建和真机验证。

## 构建与发布

- [原生项目构建](development/building.md)：Windows、Ninja、Linux、macOS、安装和原生包。
- [Python 包构建与发布](development/python-package.md)：Conda、wheel、安装验证和发布。
- [开发路线图](development/roadmap.md)：已评审的优化建议及迭代优先级。

## 设计说明

- [实例身份与类别成员设计](design/instance-identity.md)：稳定 ID、轻量句柄和多类别成员关系。

## 文档使用约定

- `docs/dsl/` 描述规则作者需要了解的公开语言行为。
- `docs/integration/` 描述应用开发者如何调用 PostAnvil。
- `docs/development/` 描述项目构建、打包、发布和后续规划。
- `docs/design/` 记录重要设计决定，不等同于全部公开 API 承诺。

文档描述 PostAnvil 0.8.x。若具体补丁版本存在差异，请以对应版本的公开头文件、绑定和
测试结果为准。

---

[返回项目首页](../README.md) · [下一篇：DSL 快速开始](dsl/README.md)
