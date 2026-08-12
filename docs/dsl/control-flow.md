# DSL 控制流、表达式与类型

[文档中心](../README.md) · [DSL 快速开始](README.md)

## 本页目录

- [函数控制流](#函数控制流)
- [IF、ELIF 与 ELSE](#ifelif-与-else)
- [FOR 循环](#for-循环)
- [表达式与类型](#表达式与类型)
- [动态属性](#动态属性)
- [运算符优先级](#运算符优先级)

## 函数控制流

规则、函数、条件分支和循环统一使用花括号定界。`ELIF` 与 `ELSE` 既可以紧跟前一分支的
`}`，也可以另起一行；缩进只用于排版，不参与语法分析。

### IF、ELIF 与 ELSE

```postanvil
IF condition {
    statements
} ELIF other_condition {
    statements
} ELSE {
    statements
}
```

支持零个或多个 `ELIF` 和可选的 `ELSE`，也可以嵌套。分支内声明的局部变量只在该分支作用域内有效。

```postanvil
RULE FUNC level(conf: NUM) -> NUM {
    IF conf > 0.8 {
        RETURN 3
    } ELIF conf > 0.5 {
        RETURN 2
    } ELSE {
        RETURN 1
    }
}
```

### FOR 循环

```postanvil
FOR obj IN <类别表达式> {
    statements
}
```

普通类别循环中，循环变量的类型为 `INST`，可读取 `obj.conf`、`obj.area` 等属性，也可赋给其他 `INST` 变量或传入函数：

```postanvil
RULE FUNC avg_conf(cls: STR) -> NUM {
    NUM total = 0
    FOR obj IN cls {
        total = total + obj.conf
    }
    IF cls.count == 0 {
        RETURN 0
    } ELSE {
        RETURN total / cls.count
    }
}
```

`FOR cls IN "global"` 遍历类别名，因此可以嵌套遍历全部实例：

```postanvil
RULE FUNC total_area() -> NUM {
    NUM total = 0
    FOR cls IN "global" {
        FOR obj IN cls {
            total = total + obj.area
        }
    }
    RETURN total
}
```

循环体拥有独立作用域；`RETURN` 会立即结束循环和函数。空类别和不存在的类别均视为空集合，循环执行零次。

## 表达式与类型

### 字面量与访问形式

| 形式 | 示例 |
|---|---|
| 数值 | `100`、`0.5`、`.8` |
| 字符串 | `"person"`、`"hello\\\"world"` |
| 布尔 | `TRUE`、`FALSE` |
| 当前实例值 | `self`（类型为 `INST`） |
| 变量 | `threshold` |
| 当前实例属性 | `self.conf`、`self.id`、`self.index`、`self.cls` |
| 类别属性 | `"car".count`、`cls.count` |
| 图像属性 | `img.w` |
| 循环实例属性 | `obj.area` |
| 实例变量属性 | `selected.conf` |
| 动态属性 | `obj.(prop_name)` |
| 函数调用 | `avg_conf("car")`、`_SQRT(9)`、`_IOU(a, b)` |

字符串仅支持 `==` 和 `!=` 比较。表达式系统没有三元运算符、`LET`、对象构造或幂运算符；幂运算使用 `_POW(base, exponent)`。

### 动态属性

静态属性写法中的点号右侧是固定属性名：

```postanvil
obj.conf
cls.count
img.w
```

需要由字符串表达式在运行时决定属性名时，在点号后使用括号：

```postanvil
obj.(prop_name)
self.(prop_name)
cls.(prop_name)
"person".(prop_name)
img.(prop_name)
```

括号内表达式必须返回 `STR`（或运行时值为 `STR` 的 `ANY`）。属性名大小写不敏感，运行时会统一转换为大写。静态写法和动态写法互不影响：即使存在名为 `conf` 的变量，`obj.conf` 仍固定读取 `CONF` 属性，只有 `obj.(conf)` 才会读取变量 `conf` 指定的属性。

以下函数可以按属性名计算类别实例的数值平均值：

```postanvil
RULE FUNC fn_avg(_cls: STR, _prop: STR) -> NUM {
    NUM _sum = 0
    FOR _inst IN _cls {
        _sum = _sum + _inst.(_prop)
    }
    RETURN _sum / _cls.count
}
NUM avg_conf = fn_avg("person", "conf")
NUM avg_area = fn_avg("person", "area")
```

如果动态属性不存在，或属性值不能参与所在表达式要求的运算，将产生运行时错误。类别为空时当前数值除零规则会返回 `0`。

### 运算符优先级

从低到高：

| 优先级 | 运算符 |
|---|---|
| 1 | `OR` |
| 2 | `AND` |
| 3 | `NOT` |
| 4 | `>`、`<`、`>=`、`<=`、`==`、`!=` |
| 5 | `+`、`-` |
| 6 | `*`、`/` |
| 7 | 一元 `-` |

比较表达式一次只能包含一个比较运算符；需要组合多个比较时使用 `AND` 或 `OR`。数值除以零的结果为 `0`。

---

上一篇：[声明与规则](language.md) · 下一篇：[属性、内置函数与排序](reference.md)
