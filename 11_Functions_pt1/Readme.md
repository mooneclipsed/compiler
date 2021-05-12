## Functions_pt1
为编译器添加函数的功能，第一部分。
* char, int, long 三种类型
* 返回值的类型需要匹配
* 每个函数的参数个数存储
* 局部变量与全局变量

我们目前先只让这些函数可以生成代码，但是只在main（）函数中被调用。

### struct ASTnode *function_declaration(void)
parameters: void
return: ASTnode *
functions: 识别一个函数类型,执行语法检查和AST构建,目前还没有语义检测功能。

### Generate code x86-64
