grammar PostAnvil;

// ============================================================
//  PostAnvil DSL 语法 (ANTLR4 / C++ target)
//  版本 0.8.0  —  2026-08-10
// ============================================================

options {
    language = Cpp;
    caseInsensitive = true;
}

// ==================== Lexer ====================

// ---------- 规则 ----------
RULE      : 'RULE';
FILTER    : 'FILTER';
ATTR      : 'ATTR';
FUNC      : 'FUNC';
SORT      : 'SORT';
GROUP     : 'GROUP';
APPEND    : 'APPEND';
FROM      : 'FROM';

// ---------- 交互 ----------
IMPORT    : 'IMPORT';
EXPORT    : 'EXPORT';
AS        : 'AS';

// ---------- 逻辑 ----------
AND       : 'AND';
OR        : 'OR';
NOT       : 'NOT';
BOOL_LIT  : 'TRUE' | 'FALSE';

SELF      : 'SELF';

// ---------- 类型 ----------
NUM       : 'NUM';
STR       : 'STR';
BOOL      : 'BOOL';
INST      : 'INST';
ANY       : 'ANY';
ALL_INST  : 'ALL_INST';

// ---------- 控制 ----------
RETURN    : 'RETURN';
IF        : 'IF';
ELIF      : 'ELIF';
ELSE      : 'ELSE';
FOR       : 'FOR';
IN        : 'IN';
ASC       : 'ASC';
DESC      : 'DESC';

// ---------- 定界 ----------
LCURLY    : '{';
RCURLY    : '}';

// ---------- 运算 ----------
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
AT        : '@';

// ---------- 字面量 ----------
NUMBER
    : [0-9]+ ('.' [0-9]*)?
    | '.' [0-9]+
    ;

STRING
    : '"' ( ~["\\\r\n] | '\\' ~[\r\n] )* '"'
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
    : newlines*
      ( (declaration | rule_) newlines+ )*
      (declaration | rule_)?
      EOF
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
    : IMPORT importItem (',' importItem)*
    ;

importItem
    : type host=IDENTIFIER (AS local=IDENTIFIER)?
    ;

exportDef
    : EXPORT exportItem (',' exportItem)*
    ;

exportItem
    : expr AS host=IDENTIFIER
    ;

globalDef
    : type IDENTIFIER '=' expr
    | IDENTIFIER '=' expr
    ;

type
    : NUM | STR | BOOL | INST | ANY
    ;

// ============ 块 ============
condition_block
    : LCURLY
      newlines?
      ( bool_expr ( newlines bool_expr )* newlines? )?
      RCURLY
    ;

attr_block
    : LCURLY
      newlines?
      ( attr_def ( newlines attr_def )* newlines? )?
      RCURLY
    ;

sort_block
    : LCURLY
      newlines?
      sort_key ( newlines sort_key )* newlines?
      RCURLY
    ;

stmt_block
    : LCURLY
      newlines?
      ( statement ( newlines statement )* newlines? )?
      RCURLY
    ;

// ============ 规则 ============
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
    : RULE FILTER class_selector
      newlines?
      condition_block
    ;

// ATTR 规则
attr_rule
    : RULE ATTR class_selector
      newlines?
      attr_block
    ;

// GROUP 规则
group_rule
    : RULE GROUP class_expr FROM class_selector
      newlines?
      condition_block
    ;

// APPEND 规则
append_rule
    : RULE APPEND class_expr FROM class_selector
      newlines?
      condition_block
    ;

// SORT 规则
sort_rule
    : RULE SORT class_selector
      newlines?
      sort_block
    ;

// FUNC 规则
func_rule
    : RULE FUNC name=IDENTIFIER '(' typed_params? ')' (ARROW return_type=type)?
      newlines?
      stmt_block
    ;

// ============ 规则子句 ============

attr_def
    : attr_lvalue '=' expr
    ;

attr_lvalue
    : SELF '.' IDENTIFIER           # InstanceAttrDef
    | STRING '.' IDENTIFIER         # ClassAttrDef
    ;

typed_params
    : typed_param (',' typed_param)*
    ;

typed_param
    : param_name=IDENTIFIER ':' param_type=type
    ;

statement
    : type IDENTIFIER '=' expr      # StmtVarDef
    | IDENTIFIER '=' expr           # StmtAssign
    | ifStmt                        # StmtIf
    | forStmt                       # StmtFor
    | expr                          # StmtExpr
    | RETURN expr                   # StmtReturn
    ;

// --- 控制流 ---
ifStmt
    : ifBranch
      ( newlines? elifBranch )*
      ( newlines? elseBranch )?
    ;

ifBranch
    : IF expr
      newlines?
      stmt_block
    ;

elifBranch
    : ELIF expr
      newlines?
      stmt_block
    ;

elseBranch
    : ELSE
      newlines?
      stmt_block
    ;

forStmt
    : FOR IDENTIFIER IN for_source
      newlines?
      stmt_block
    ;

sort_key
    : expr direction
    ;

direction
    : ASC
    | DESC
    ;

// ==================== 表达式 ====================

class_expr
    : STRING
    | IDENTIFIER
    | ALL_INST
    ;

// 类别选择器：逗号列表是临时类别组；@ 开头名称保留给内置/未来命名组。
class_selector
    : class_expr (COMMA class_expr)*
    | class_group
    ;

class_group
    : AT IDENTIFIER
    ;

for_source
    : class_expr
    | class_group
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
