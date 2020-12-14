## l-value和r-value的声明

修改的时候，lvalue是一个值绑定一个地址，而rvalue是一个值不绑定特定位置。
lvalue是长久存在的，rvalue是用完就丢弃的。

### 扩充lvalues
A_LVIDENT. 把它加入gensAST().
修改=在token types中的位置，同时=优先级很低，我们修改expr.c 中的OpPrec[]。

### 修改解析器
删除了print_statement()和assignment_statement()。
删除了T_PRINT和'print'关键字.

### 表达式解析
在生成左侧左值代码之前为右侧右值生成汇编代码。
必须在表达式解析器中完成这一点。
赋值表达式是右关联的:运算符绑定到右边的表达式比绑定到左边的表达式更紧密。

增加 rightassoc(),修改binexpr().