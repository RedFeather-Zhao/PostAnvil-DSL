grammar PostAnvil;

// ============================================================
//  PostAnvil DSL 语法定义 (ANTLR4 / C++ target)
//  版本 0.7  —  2026-08-07   (花括号块语法)
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
    language = Cpp;
    caseInsensitive = true;
}

// ==================== 词法规则 (Lexer) ====================

// ---------- 关键字 ----------
RULE      : 'RULE';
FILTER    : 'FILTER';
ATTR      : 'ATTR';
FUNC      : 'FUNC';
GROUP     : 'GROUP';
APPEND    : 'APPEND';
FROM      : 'FROM';
AND       : 'AND';
OR        : 'OR';
NOT       : 'NOT';
SELF      : 'SELF';
NUM       : 'NUM';
STR       : 'STR';
BOOL      : 'BOOL';
INST      : 'INST';
ANY       : 'ANY';
RETURN    : 'RETURN';
IMPORT    : 'IMPORT';
EXPORT    : 'EXPORT';
AS        : 'AS';
IF        : 'IF';
ELIF      : 'ELIF';
ELSE      : 'ELSE';
FOR       : 'FOR';
IN        : 'IN';
SORT      : 'SORT';
ASC       : 'ASC';
DESC      : 'DESC';

// ---------- 花括号（块定界符） ----------
LCURLY    : '{';
RCURLY    : '}';

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
    : [0-9]+ ('.' [0-9]*)?
    | '.' [0-9]+
    ;

STRING
    : '"' ( ~["\\] | '\\' . )* '"'
    ;

IDENTIFIER
    : [a-z_] [a-z0-9_]*
    ;

// ---------- 空白与注释 ----------
WS
    : [ \t]+ -> skip
    ;

LINE_CONTINUATION
    : '\\' [ \t]* '\r'? '\n' -> skip
    ;

NEWLINE
    : '\r'? '\n'
    ;

COMMENT
    : ( '#' | '//' ) ~[\r\n]* -> skip
    ;


// ==================== Parser ====================

program
    : ( declaration | rule_ | newlines )* EOF
    ;

newlines
    : (NEWLINE)+
    ;

// ============ 顶层声明 ============
declaration
    : importDef
    | exportDef
    | globalDef
    ;

importDef
    : IMPORT importItem (',' importItem)* newlines
    ;

importItem
    : type host=IDENTIFIER (AS local=IDENTIFIER)?
    ;

exportDef
    : EXPORT exportItem (',' exportItem)* newlines
    ;

exportItem
    : expr AS host=IDENTIFIER
    ;

globalDef
    : type IDENTIFIER '=' expr newlines
    | IDENTIFIER '=' expr newlines
    ;

type
    : NUM | STR | BOOL | INST | ANY
    ;

// ============ 规则块 ============
rule_
    : filter_rule
    | attr_rule
    | group_rule
    | append_rule
    | sort_rule
    | func_rule
    ;

// FILTER 规则
filter_rule
    : RULE FILTER class_expr LCURLY
      newlines?
      ( bool_expr newlines )*
      newlines?
      RCURLY
    ;

// ATTR 规则
attr_rule
    : RULE ATTR class_expr LCURLY
      newlines?
      ( attr_def newlines )*
      newlines?
      RCURLY
    ;

attr_def
    : attr_lvalue '=' expr
    ;

attr_lvalue
    : SELF '.' IDENTIFIER           # InstanceAttrDef
    | STRING '.' IDENTIFIER         # ClassAttrDef
    ;

// FUNC 规则
func_rule
    : RULE FUNC name=IDENTIFIER '(' typed_params? ')' (ARROW return_type=type)?
      LCURLY
      newlines?
      ( func_statement newlines )+
      newlines?
      RCURLY
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
    : IF expr LCURLY
      newlines?
      ( func_statement newlines )*
      newlines?
      RCURLY
      ( elifBranch )*
      ( elseBranch )?
    ;

elifBranch
    : ELIF expr LCURLY
      newlines?
      ( func_statement newlines )*
      newlines?
      RCURLY
    ;

elseBranch
    : ELSE LCURLY
      newlines?
      ( func_statement newlines )*
      newlines?
      RCURLY
    ;

forStmt
    : FOR IDENTIFIER IN class_expr LCURLY
      newlines?
      ( func_statement newlines )*
      newlines?
      RCURLY
    ;

// GROUP 规则
group_rule
    : RULE GROUP class_expr FROM class_expr LCURLY
      newlines?
      ( bool_expr newlines )*
      newlines?
      RCURLY
    ;

// APPEND 规则
append_rule
    : RULE APPEND class_expr FROM class_expr LCURLY
      newlines?
      ( bool_expr newlines )*
      newlines?
      RCURLY
    ;

// SORT 规则
sort_rule
    : RULE SORT class_expr LCURLY
      newlines?
      ( sort_key newlines )+
      newlines?
      RCURLY
    ;

sort_key
    : expr direction
    ;

direction
    : ASC
    | DESC
    ;

// ==================== 表达式系统 ====================

class_expr
    : STRING
    | IDENTIFIER
    ;

bool_expr
    : or_expr
    ;

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

primary
    : NUMBER
    | STRING
    | BOOL_LIT
    | SELF
    | func_call
    | attribute
    | '(' expr ')'
    | IDENTIFIER
    ;

func_call
    : IDENTIFIER '(' (expr (',' expr)*)? ')'
    ;

attribute
    : SELF '.' IDENTIFIER             # InstanceAttr
    | STRING '.' IDENTIFIER           # ClassAttr
    | IDENTIFIER '.' IDENTIFIER       # VarInstanceAttr
    | SELF '.' '(' expr ')'           # DynamicInstanceAttr
    | STRING '.' '(' expr ')'         # DynamicClassAttr
    | IDENTIFIER '.' '(' expr ')'     # DynamicVarAttr
    ;

comp_op
    : '>' | '<' | '>=' | '<=' | '==' | '!='
    ;

add_op
    : '+' | '-'
    ;

mul_op
    : '*' | '/'
    ;
