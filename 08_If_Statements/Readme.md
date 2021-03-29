# If Statements
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
 if_statement: if_head
      |        if_head 'else' compound_statement
      ;

 if_head: 'if' '(' true_false_expression ')' compound_statement  ;
```

## 转换为汇编
需要用到 jump指令。

## 改变

之前，在statement中，我们调用print_statement(), compound_statement(),他们会自己调用genAST()来生成表达式
现在， 我希望在statement中，返回一个AST 树，然后只生产一颗AST树，调用genAST。

现在还不打算解决像 if (x-2) 表达式
所以先限制一下比较操作符A_EQ, A_NE, A_LT, A_GT, A_LE or A_GE.

### Glue 
添加一个glue ast node， 我们构造单棵ast树，然后用glue把他们连接在一起。
```c
 if (left != NULL)
     left = mkastnode(A_GLUE, left, NULL, tree, 0);
```

### code generator
我们需要考虑当if判断后，跳跃的操作。

```c
// List of inverted jump instructions,
// in AST order: A_EQ, A_NE, A_LT, A_GT, A_LE, A_GE
static char *invcmplist[] = { "jne", "je", "jge", "jle", "jg", "jl" };

int cgcompare_and_jump(int ASTop, int r1, int r2, int label){
  if(ASTop < A_EQ || ASTop > A_GE)
    fatal("Bad ASTop in cgcompare_and_set()");

  fprintf(Outfile, "\tcmpq\t%s, %s\n", reglist[r2], reglist[r1]);
  fprintf(Outfile, "\t%s\tL%d\n", invcmplist[ASTop - A_EQ], label);
  freeall_registers();
  return (NOREG);
}
```
定义了一个invcmplist， 主要是为了方便生成汇编中的jmp指令，当不符合条件，也就是恰好与astTop的描述相反的时候，跳跃到false的statement，后续因为要修改conAST的内容，所以还会优化。

```c
// List of comparison instructions,
// in AST order: A_EQ, A_NE, A_LT, A_GT, A_LE, A_GE
static char *cmplist[] =
  { "sete", "setne", "setl", "setg", "setle", "setge" };

// Compare two registers and set if true.
int cgcompare_and_set(int ASTop, int r1, int r2) {

  // Check the range of the AST operation
  if (ASTop < A_EQ || ASTop > A_GE)
    fatal("Bad ASTop in cgcompare_and_set()");

  fprintf(Outfile, "\tcmpq\t%s, %s\n", reglist[r2], reglist[r1]);
  fprintf(Outfile, "\t%s\t%s\n", cmplist[ASTop - A_EQ], breglist[r2]);
  fprintf(Outfile, "\tmovzbq\t%s, %s\n", breglist[r2], reglist[r2]);
  free_register(r1);
  return (r2);
}

```

