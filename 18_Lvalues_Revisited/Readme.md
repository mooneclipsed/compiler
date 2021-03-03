## l-value和r-value的声明

修改的时候，lvalue是一个值绑定一个地址，而rvalue是一个值不绑定特定位置。
lvalue是长久存在的，rvalue是用完就丢弃的。

l-value may appear as either left hand or right hand side of an assignment operator(=).
l-value often represents as identifier.
```
// declare a an object of type 'int' 
int a; 

// a is an expression referring to an 
// 'int' object as l-value 
a = 1; 

int b = a; // Ok, as l-value can appear on right 

// Switch the operand around '=' operator 
9 = a; 

// Compilation error: 
// as assignment is trying to change the 
// value of assignment operator 
```

R-value: r-value” refers to data value that is stored at some address in memory. A r-value is an expression that can’t have a value assigned to it which means r-value can appear on right but not on left hand side of an assignment operator(=).

### 扩充lvalues
A_LVIDENT. 把它加入gensAST().
修改=在token types中的位置，同时=优先级很低，我们修改expr.c 中的OpPrec[]。

### 修改解析器
删除了print_statement()和assignment_statement()。
删除了T_PRINT和'print'关键字.
增加了single_statement
可以将2+3 看作成一个合法的模块




### 表达式解析
在生成左侧左值代码之前为右侧右值生成汇编代码。
必须在表达式解析器中完成这一点。
赋值表达式是右关联的:运算符绑定到右边的表达式比绑定到左边的表达式更紧密。

增加 rightassoc(),assign是右结合的,
修改binexpr(), 当ASTop = assign当时候，我们需要交换一下左右子树。


## QUESTION
我们需要在生成左值的代码之前生成右值的程序集代码。我们过去在语句解析器中这样做，现在我们必须在表达式解析器中这样做。

赋值表达式是右结合式的:操作符与右侧表达式的绑定比与左侧表达式的绑定更紧密。