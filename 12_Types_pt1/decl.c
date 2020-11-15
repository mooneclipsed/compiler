#include "defs.h"
#include "data.h"
#include "decl.h"

// Parsing of declarations


// Parse the current token and 
// return a primitive type enum value
int parse_type(int t) {
  switch (t)
  {
  case T_CHAR:
    return (P_CHAR);
  case T_INT:
    return (P_INT);
  case T_VOID:
    return (P_VOID);
  
  default:
    fatald("Illegal type, token", t);
    break;
  }
}

// Parse the declaration of a variable
void var_declaration(void) {
  int id, type;

  // Get the type of the variable, then the identifier
  type = parse_type(Token.token);
  scan(&Token);
  ident();
  id = addglob(Text, type, S_VARIABLE);
  genglobsym(id);
  semi();
}

// Parse the declaration of a simplistic function
struct ASTnode *function_declaration(void){
  struct ASTnode *tree;
  int nameslot, type;

  
  // Find the 'void', the identifier, and the "(" ")".
  type = parse_type(Token.token);
  scan(&Token);
  ident();
  nameslot = addglob(Text, type, S_FUNCTION);
  lparen();
  rparen();

  // Get the AST tree for the compound statement
  tree = compound_statement();
  return (mkastunary(A_FUNCTION, P_VOID, tree, nameslot));
}
