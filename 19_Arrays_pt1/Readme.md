## Array, part1
仅仅为1纬数组。

* 声明固定大小的数组不包括初始化列表

* 数组的索引为表达式的右值

* 数组的索引作为赋值的左值

* 添加括号表达，如*(ptr + 2)等价于ptr[2].

* BNF

primary_expression
        : IDENTIFIER
        | CONSTANT
        | STRING_LITERAL
        | '(' expression ')'
        ;

postfix_expression
        : primary_expression
        | postfix_expression '[' expression ']'
          ...

* array_assess()

  left = mkastnode(A_ADD, Gsym[id].type, left, NULL, right, 0);
  left = mkastunary(A_DEREF, value_at(left->type), left, 0);
  return (left);
  返回一个AST树， 其中数组的基数组已经添加了偏移量，并对元素进行解引用，
  在此仍然是左值

   b[3]= 12; a= b[3];
   ```
    A_INTLIT 12
  A_WIDEN
      A_ADDR b
        A_INTLIT 3    # 3 is scaled by 4
      A_SCALE 4
    A_ADD             # and then added to b's address
  A_DEREF             # and derefenced. Note, stll an lvalue
A_ASSIGN

      A_ADDR b
        A_INTLIT 3    # As above
      A_SCALE 4
    A_ADD
  A_DEREF rval        # but the dereferenced address will be an rvalue
  A_IDENT a
A_ASSIGN
   ```

   
   ```
        movq    $12, %r8
        leaq    b(%rip), %r9    # Get b's address
        movq    $3, %r10
        salq    $2, %r10        # Shift 3 by 2, i.e. 3 * 4
        addq    %r9, %r10       # Add to b's address
        movq    %r8, (%r10)     # Save 12 into b[3]

        leaq    b(%rip), %r8    # Get b's address
        movq    $3, %r9
        salq    $2, %r9         # Shift 3 by 2, i.e. 3 * 4
        addq    %r8, %r9        # Add to b's address
        movq    (%r9), %r9      # Load b[3] into %r9
        movl    %r9d, a(%rip)   # and store in a
   ```


   ## Points
   1. getting the AST tree nodes correct to scale
   2. add the base address
   3. set as lvalue/rvalue