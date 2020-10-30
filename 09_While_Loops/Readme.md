```
 compound_statement: '{' '}'          // empty, i.e. no statement
      |      '{' statement '}'
      |      '{' statement statements '}'
      ;

 statement: print_statement
      |     declaration
      |     assignment_statement
      |     if_statement
      ;

 print_statement: 'print' expression ';'  ;

 declaration: 'int' identifier ';'  ;

 assignment_statement: identifier '=' expression ';'   ;

 if_statement: if_head
      |        if_head 'else' compound_statement
      ;

 if_head: 'if' '(' true_false_expression ')' compound_statement  ;
```

generate a single AST tree for the whole input with the parser.

为整个输入构建单个大的AST tree



recursive descent parser

暂时if（）只处理A_EQ, A_NE, A_LT, A_GT, A_LE or A_GE 

6种状态

A if tree.

```
                      IF
                    / |  \
                   /  |   \
                  /   |    \
                 /    |     \
                /     |      \
               /      |       \
      condition   statements   statements
```

我们把新获得的子树与现在存在的树连接起来。