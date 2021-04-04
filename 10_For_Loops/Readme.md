## For_Loops

### The FOR LOOP Syntax
for_statement: 'for' '(' preop_statement ';'
                          true_false_expression ';'
                          postop_statement ')' compound_statement  ;
 preop_statement:  statement  ;        (for now)
 postop_statement: statement  ;        (for now)                 

 
### Parsing Statements
我们需要分离statement， 以便compound_statement()调用single_statement()就可以获得一个statement。

```c
// Parse a single statement
// and return its AST
static struct ASTnode *single_statement(void) {
  switch (Token.token) {
    case T_PRINT:
      return (print_statement());
    case T_INT:
      var_declaration();
      return (NULL);		// No AST generated here
    case T_IDENT:
      return (assignment_statement());
    case T_IF:
      return (if_statement());
    case T_WHILE:
      return (while_statement());
    case T_FOR:
      return (for_statement());
    default:
      fatald("Syntax error, token", Token.token);
  }
}

// Parse a compound statement
// and return its AST
struct ASTnode *compound_statement(void) {
  struct ASTnode *left = NULL;
  struct ASTnode *tree;

  // Require a left curly bracket
  lbrace();

  while (1) {
    // Parse a single statement
    tree = single_statement();

    // Some statements must be followed by a semicolon
    if (tree != NULL &&
	(tree->op == A_PRINT || tree->op == A_ASSIGN))
      semi();

    // For each new tree, either save it in left
    // if left is empty, or glue the left and the
    // new tree together
    if (tree != NULL) {
      if (left == NULL)
	left = tree;
      else
	left = mkastnode(A_GLUE, left, NULL, tree, 0);
    }
    // When we hit a right curly bracket,
    // skip past it and return the AST
    if (Token.token == T_RBRACE) {
      rbrace();
      return (left);
    }
  }
}
```

### for_statement()
         A_GLUE
        /     \
   preop     A_WHILE
             /    \
        decision  A_GLUE
                  /    \
            compound  postop



### static struct ASTnode *single_statement(void)
描述：为单个模块生成一颗ast树。
返回值： astnode指针。
目前返回的类型分为 print， var， assignment， if， while, for几种类型。

### struct ASTnode *compound_statement(void)
描述：用glue结点将单个ast树连接起来生成一颗混合的ast树，以便与生成汇编代码。
返回值： astnode指针。
正常情况，当遇到'}'退出模块。
