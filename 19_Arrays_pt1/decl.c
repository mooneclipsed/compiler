#include "defs.h"
#include "data.h"
#include "decl.h"

// Parsing of declarations



// Parse the current token and
// return a primitive type enum value
int parse_type(void) {
  int type;
  switch (Token.token) {
    case T_VOID: type = P_VOID; break;
    case T_CHAR: type = P_CHAR; break;
    case T_INT:  type = P_INT;  break;
    case T_LONG: type = P_LONG; break;
    default:
      fatald("Illegal type, token", Token.token);
  }

  // Scan in one or more further '*' tokens - T_STAR
  // and determine the correct pointer type
  while (1){
    scan(&Token);
    if (Token.token != T_STAR) break;
    type = pointer_to(type);
  }
  return (type);
}

// variable_declaration: 'int' identifier ';'  ;
// Parse the declaration of a variable
void var_declaration(int type) {
  int id;

  while(1) {
    // Text now has the identifier's name
    // Add it as a konwn identifier
    // and generate its space in assembly
    id = addglob(Text, type, S_VARIABLE, 0);
    genglobsym(id);

    if (Token.token == T_SEMI) {
      scan(&Token);
      return;
    }
    // If the next token is a comma, skip it
    // get the identifier and loop back
    if (Token.token == T_COMMA) {
      scan(&Token);
      ident();
      continue;
    }
    fatal("Missing , or ; after identifier");
  }
}

// For now we have a very simplistic function definition grammar
//
// function_declaration: 'void' identifier '(' ')' compound_statement   ;
//
// Parse the declaration of a simplistic function
struct ASTnode *function_declaration(int type) {
  struct ASTnode *tree, *finalstmt;
  int nameslot, endlabel;

  // Text now has the identifier's name
  // Get a label-id for the end label, add the function
  // to the symbol table, and set the Functionid global
  // to the function's symbol-id
  endlabel = genlabel();
  nameslot = addglob(Text, type, S_FUNCTION, endlabel);
  Functionid = nameslot;

  lparen();
  rparen();

  // Get the AST tree for the compound statement
  tree = compound_statement();

  // If the function type isn't P_VOID, 

  if (type != P_VOID) {
    // error if no statements in the function
    if (tree == NULL)
      fatal("No statements in functuon with non-void type");

    // Check that the last AST operation in the
    // compound statement was a return statement
    finalstmt = (tree->op == A_GLUE) ? tree->right : tree;
    if (finalstmt == NULL || finalstmt->op != A_RETURN)
      fatal("No return for function with non-void type");
  }

  // Return an A_FUNCTION node which has the function's nameslot
  // and the compound statement sub-tree
  return (mkastunary(A_FUNCTION, type, tree, nameslot));
}

// Parse one or more global declarations, either
// variables or functions
void global_declarations(void) {
  struct ASTnode *tree;
  int type;

  while (1) {

    // We have to read past the type and identifier
    // to see either a '(' for a function_declaration
    // or a ',' or ';' for a var_declaration.
    // Text is filled in by the ident() call
    type = parse_type();
    ident();
    if (Token.token == T_LPAREN) {
      tree = function_declaration(type);
      if (O_dumpAST) {
        dumpAST(tree, NOLABEL, 0);
        fprintf(stdout, "\n\n");
      }
      genAST(tree, NOREG, 0);
    } else {
      var_declaration(type);
    }

    if (Token.token == T_EOF)
      break;
  }
}