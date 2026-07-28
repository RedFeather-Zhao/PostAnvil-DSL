grammar PostAnvil;

// ============================================================
//  PostAnvil DSL 语法定义 (ANTLR4 / C++ target)
//  版本 0.6  —  2026-07-28
// ============================================================
//  功能概览：
//    - 目标检测后处理 DSL
//    - 规则块：FILTER、ATTR、FUNC、GROUP、APPEND、SORT
//    - 内置对象：self (当前实例)、img (图像尺寸)
//    - 类型：NUM、STR、BOOL、INST、ANY
//    - 控制流：IF-ELSE、FOR 循环 (仅函数内)
//    - 原地稳定排序规则：SORT
//    - 与宿主交互：IMPORT、EXPORT
//    - 大小写不敏感，支持 # 和 // 注释
// ============================================================

options {
    language = Cpp;          // 生成 C++ 代码
    caseInsensitive = true;  // 关键字、标识符不区分大小写
}

// ==================== 词法规则 (Lexer) ====================

// ---------- 关键字 ----------
RULE      : 'RULE';           // 规则开始
RULEEND   : 'RULEEND';        // 规则结束
FILTER    : 'FILTER';         // 过滤规则
ATTR      : 'ATTR';           // 属性规则
FUNC      : 'FUNC';           // 自定义函数
GROUP     : 'GROUP';          // 创建新类别
APPEND    : 'APPEND';         // 追加实例
FROM      : 'FROM';           // 指定来源类别
AND       : 'AND';            // 逻辑与
OR        : 'OR';             // 逻辑或
NOT       : 'NOT';            // 逻辑非
SELF      : 'SELF';           // 当前实例对象
NUM       : 'NUM';            // 数值类型
STR       : 'STR';            // 字符串类型
BOOL      : 'BOOL';           // 布尔类型
INST      : 'INST';           // 检测实例快照类型
ANY       : 'ANY';            // 任意类型
RETURN    : 'RETURN';         // 函数返回语句
IMPORT    : 'IMPORT';         // 导入宿主变量
EXPORT    : 'EXPORT';         // 导出结果到宿主
AS        : 'AS';             // 别名关键字
IF        : 'IF';             // 条件分支开始
ELIF      : 'ELIF';           // 条件分支嵌套
ELSE      : 'ELSE';           // 条件分支否则
ENDIF     : 'ENDIF';          // 条件分支结束
FOR       : 'FOR';            // 循环开始
IN        : 'IN';             // 循环遍历指定类别
ENDFOR    : 'ENDFOR';         // 循环结束
SORT      : 'SORT';           // 原地排序规则
ASC       : 'ASC';            // 升序
DESC      : 'DESC';           // 降序

// ---------- 布尔字面量 ----------
BOOL_LIT  : 'TRUE' | 'FALSE';

// ---------- 运算符 ----------
ARROW     : '->';
PLUS      : '+';
MINUS     : '-';
STAR      : '*';
SLASH     : '/';
LT        : '<';
GT        : '>';
LE        : '<=';
GE        : '>=';
EQ        : '==';
NE        : '!=';
DOT       : '.';
LPAREN    : '(';
RPAREN    : ')';
COMMA     : ',';
ASSIGN    : '=';

// ---------- 字面量 ----------
NUMBER
    : [0-9]+ ('.' [0-9]*)?   // 整数或小数
    | '.' [0-9]+              // 以点开头的纯小数
    ;

STRING
    : '"' ( ~["\\] | '\\' . )* '"'  // 双引号字符串，支持 \" 和 \\ 转义
    ;

IDENTIFIER
    : [a-z_] [a-z0-9_]*       // 标识符：字母/下划线开头，后续可含数字
    ;

// ---------- 空白与注释 ----------
WS
    : [ \t]+ -> skip           // 空格和制表符跳过
    ;

NEWLINE
    : '\r'? '\n'               // 换行符（作为语句分隔）
    ;

COMMENT
    : ( '#' | '//' ) ~[\r\n]* -> skip   // 行注释（# 或 //）
    ;


// ==================== Parser ====================

// 程序顶层结构：
// 包含 变量声明 或 规则声明
// 
program
    : ( declaration | rule_ | newlines )*
      EOF
    ;

newlines
    : (NEWLINE)+
    ;

// ============ outside rule ============

// 变量声明：
// 包含 导入定义|导出定义|全局定义
// 
declaration
    : importDef
    | exportDef
    | globalDef
    ;

// 导入宿主变量
// 
importDef
    : IMPORT importItem (',' importItem)* newlines
    ;

importItem
    : type host=IDENTIFIER (AS local=IDENTIFIER)?   // 类型 宿主名 [AS 本地别名]
    ;

// 导出程序变量
// 
exportDef
    : EXPORT exportItem (',' exportItem)* newlines
    ;

exportItem
    : expr AS host=IDENTIFIER        // 表达式 AS 宿主变量名
    ;

// 声明/赋值变量
// 
globalDef
    : type IDENTIFIER '=' expr newlines
    | IDENTIFIER '=' expr newlines
    ;

type
    : NUM | STR | BOOL | INST | ANY  // 值类型
    ;

// ============ inside rule ============

// 规则块声明 - 每个规则块都针对类别组进行操作（除函数块）
// 
// 
rule_
    : filter_rule
    | attr_rule
    | group_rule
    | append_rule
    | sort_rule
    | func_rule
    ;

// FILTER 规则，组内实例过滤
// 行间自动 AND，每行一个布尔表达式，禁止赋值
filter_rule
    : RULE FILTER class_expr ':' newlines
      ( bool_expr newlines )*
      RULEEND
    ;

// --- ATTR 规则（定义实例属性或类型属性） ---
attr_rule
    : RULE ATTR class_expr ':' newlines
      ( attr_def newlines )*
      RULEEND
    ;

attr_def
    : attr_lvalue '=' expr
    ;

attr_lvalue
    : SELF '.' IDENTIFIER           # InstanceAttrDef     // self.xxx = expr
    | STRING '.' IDENTIFIER         # ClassAttrDef       // "class".xxx = expr
    ;

// --- FUNC 规则（自定义函数） ---
func_rule
    : RULE FUNC name=IDENTIFIER '(' typed_params? ')' (ARROW return_type=type)? ':' newlines
      ( func_statement newlines )+
      RULEEND
    ;

typed_params
    : typed_param (',' typed_param)*
    ;

typed_param
    : param_name=IDENTIFIER ':' param_type=type
    ;

func_statement
    : type IDENTIFIER '=' expr      # FuncVarDef
    | IDENTIFIER '=' expr           # FuncAssign
    | ifStmt                        # FuncIfStmt
    | forStmt                       # FuncForStmt
    | expr                          # FuncExprStmt
    | RETURN expr                   # FuncReturnStmt
    ;

// --- 控制流 ---
ifStmt
    : IF expr newlines
      ( func_statement newlines )*           // IF 分支体
      ( elifBranch )*                        // 零个或多个 ELIF 分支
      ( elseBranch )?                        // 可选的 ELSE 分支
      ENDIF
    ;

elifBranch
    : ELIF expr newlines
      ( func_statement newlines )*
    ;

elseBranch
    : ELSE newlines
      ( func_statement newlines )*
    ;

forStmt
    : FOR IDENTIFIER IN class_expr newlines   // FOR 循环变量 IN 类别
      ( func_statement newlines )*
      ENDFOR
    ;

// --- GROUP 规则（创建新类别） ---
group_rule
    : RULE GROUP class_expr FROM class_expr ':' newlines
      ( bool_expr newlines )*
      RULEEND
    ;

// --- APPEND 规则（向已有类别追加实例） ---
append_rule
    : RULE APPEND class_expr FROM class_expr ':' newlines
      ( bool_expr newlines )*
      RULEEND
    ;

// --- SORT 规则（原地稳定排序） ---
// 每个排序键只求值一次；多行排序键按书写顺序组成字典序比较。
sort_rule
    : RULE SORT class_expr ':' newlines
      ( sort_key newlines )+
      RULEEND
    ;

sort_key
    : expr direction
    ;

direction
    : ASC
    | DESC
    ;

// ==================== 表达式系统 ====================

// 类别表达式：只能是字符串字面量或字符串变量
class_expr
    : STRING
    | IDENTIFIER
    ;

// FILTER 中使用的顶层布尔表达式（语义上应为 BOOL）
bool_expr
    : or_expr
    ;

// 通用表达式入口
expr
    : or_expr
    ;

or_expr
    : and_expr (OR and_expr)*
    ;
and_expr
    : not_expr (AND not_expr)*
    ;
not_expr
    : NOT not_expr
    | cmp_expr
    ;
cmp_expr
    : add_expr (comp_op add_expr)?
    ;
add_expr
    : mul_expr (add_op mul_expr)*
    ;
mul_expr
    : unary_expr (mul_op unary_expr)*
    ;
unary_expr
    : MINUS unary_expr
    | primary
    ;

// 原子表达式
primary
    : NUMBER
    | STRING
    | BOOL_LIT
    | SELF              // 当前实例值（INST）
    | func_call
    | attribute
    | '(' expr ')'
    | IDENTIFIER        // 变量
    ;

// 普通函数调用
func_call
    : IDENTIFIER '(' (expr (',' expr)*)? ')'
    ;

// 属性访问
attribute
    : SELF '.' IDENTIFIER             # InstanceAttr          // self.xxx
    | STRING '.' IDENTIFIER           # ClassAttr             // "class".xxx
    | IDENTIFIER '.' IDENTIFIER       # VarInstanceAttr       // img.xxx / inst.xxx / cls.xxx
    | SELF '.' '(' expr ')'           # DynamicInstanceAttr   // self.(prop_expr)
    | STRING '.' '(' expr ')'         # DynamicClassAttr      // "class".(prop_expr)
    | IDENTIFIER '.' '(' expr ')'     # DynamicVarAttr        // inst.(prop_expr) / cls.(prop_expr)
    ;

// 运算符分组
comp_op
    : '>' | '<' | '>=' | '<=' | '==' | '!='
    ;
add_op
    : '+' | '-'
    ;
mul_op
    : '*' | '/'
    ;
