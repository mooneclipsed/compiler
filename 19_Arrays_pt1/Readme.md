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