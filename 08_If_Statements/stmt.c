#include "defs.h"
#include "data.h"
#include "decl.h"

// Parsing of statements


// statements: statement
//      |      statement statements
//      ;
//
// statement: 'print' expression ';'
//      |     'int'   identifier ';'
//      |     identifier '=' expression ';'
//      ;
//
// identifier: T_IDENT
//      ;

static struct ASTnode *print_statement(void) {
  struct ASTnode *tree;
  int reg;

  // Match a 'print' as the first token
  match(T_PRINT, "print");

  // Parse the following expression and
  tree = binexpr(0);

 tree = mkastunary(A_PRINT, tree, 0);

  // Match the following semicolon
  semi();
  return (tree);
}

static struct ASTnode *assignment_statement(void) {
  struct ASTnode *left, *right, *tree;
  int id;

  // Ensure we have an identifier
  ident();

  // Check it's been defined then make a leaf node for it
  if ((id = findglob(Text)) == -1) {
    fatals("Undeclared variable", Text);
  }
  right = mkastleaf(A_LVIDENT, id);

  // Ensure we have an equals sign
  match(T_ASSIGN, "=");

  // Parse the following expression
  left = binexpr(0);

  // Make an assignment AST tree
  tree = mkastnode(A_ASSIGN, left, NULL, right, 0);

  // Match the following semicolon
  semi();
  return (tree);
}

// Parse an IF statement including
// any optional ELSE clause
// and return its AST
struct ASTnode *if_statement(void){
  struct ASTnode *condAST, *trueAST, *falseAST = NULL;

  // Ensure we have 'if' '('
  match(T_IF, "if");
  lparen();

  // Parse the following expression
  // and the ')' following. Ensure
  // the tree's operation is a comparsion
  condAST = binexpr(0);

  if(condAST->op < A_EQ || condAST->op > A_GE)
    fatal("Bad comparsion operator");
  rparen();

  // Get the AST for the compound statement
  trueAST = compund_statement();

  // If we have an 'else', skip it
  // and get the AST for the compound statement
  if(Token.token == T_ELSE){
    scan(&Token);
    falseAST = compund_statement();
  }
  // Build and return the AST for this statement
  return (mkastnode(A_IF, condAST, trueAST, falseAST, 0));
}



// Parse a compound statement
// and return its AST
struct ASTnode *compund_statement(void){
  struct ASTnode *left = NULL;
  struct ASTnode *tree;

  // Require a left curly bracket
  lbrace();
  while (1){
      switch (Token.token){
      case T_PRINT:
        tree = print_statement();
        break;
      case T_INT:
        var_declaration();
        break;
      case T_IDENT:
        tree = assignment_statement();
        break;
      case T_IF:
        tree = if_statement();
        break;
      case T_RBRACE:
        rbrace();
        return (left);
      default:
        fatald("Syntax error, token", Token.token);
      }
  }

  // For each new tree, either save it in left
  // if left is empty, or glue the left and the
  // new tree together
  if(tree){
    if(left == NULL)
      left = tree;
    else
      left = mkastnode(A_GLUE, left, NULL, tree, 0);
  }
  
}
