# C++ 接入

[文档中心](../README.md) · [原生项目构建](../development/building.md)

## 本页目录

- [链接 PostAnvil](#链接-postanvil)
- [创建并执行规则](#创建并执行规则)
- [实例身份和类别成员](#实例身份和类别成员)
- [错误处理](#错误处理)

## 链接 PostAnvil

源码树内直接链接：

```cmake
add_subdirectory(path/to/PostAnvil)
target_link_libraries(my_app PRIVATE PostAnvil::static)
```

使用发布预设编译并安装：

```bash
cmake --preset ninja-release
cmake --build --preset ninja-release-install
```

其中 `ninja-release-install` 会自动安装到 `out/install/release`。图形界面中选择
`Ninja Release - 编译并安装`，然后执行“生成 → 全部生成”具有相同效果。

```cmake
find_package(PostAnvil CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE PostAnvil::static) # 或 PostAnvil::shared
```

最小 C++ 代码：

```cpp
#include <PostAnvil.h>

postanvil::Compiler compiler;
auto program = compiler.compile(source);
postanvil::Scene result = program.evaluate(input_scene);
```


## 创建并执行规则

公开 C++ API 使用 `PostAnvil.h` 作为统一包含头。ANTLR、Listener 和内部算子管道均不属于
公共接口，使用者无需包含 ANTLR 头文件或直接链接独立的 ANTLR Runtime。

```cpp
#include <PostAnvil.h>

using namespace postanvil;

std::string source = R"(
    IMPORT NUM min_conf
    RULE FILTER "person" {
        self.conf > min_conf
    }
    EXPORT "person".count AS kept
)";

Compiler compiler;
Program program = compiler.compile(source);

Scene scene(Image{640, 480});
scene.add("person", Instance(10, 20, 80, 120, 0.90));
scene.add("person", Instance(30, 40, 60, 100, 0.40));
scene.add_import("MIN_CONF", 0.60);

Scene result = program.evaluate(scene);
double kept = result.get_export("kept").as_num();
```

## 实例身份和类别成员

C++ 可向 Scene 添加实例，再导入、导出轻量 `INST` 句柄：

```cpp
InstanceHandle anchor = scene.add(
	"anchor", Instance(10, 20, 80, 120, 0.75));
scene.add_import("ANCHOR", Val(anchor));

Val selected = result.get_export("selected_anchor");
InstanceId id = selected.as_inst().id;
double confidence = result.inst(id).conf();
```

同一 ID 可以同时存在于多个类别中，但始终指向 Scene 中的同一个 `Instance`。类别操作只
改变成员关系，不会隐式复制检测框。

## 错误处理

- `compile()` 在词法、语法或静态检查失败时抛出 `PACompileError`；通过
  `error.kind()` 可区分 `Syntax`、`Semantic` 和 `Internal`。
- `evaluate()` 在缺少导入值、类型不匹配、类别/属性不存在等情况下抛出
  `PARuntimeError`。
- 类别和 DSL 内部名称会统一为大写；宿主注入变量时建议直接使用大写键。
- `Program` 只支持移动，不支持复制；应在需要重复处理多个场景时复用同一已编译程序。

---

[文档中心](../README.md) · 下一篇：[Python 接入](python.md)
