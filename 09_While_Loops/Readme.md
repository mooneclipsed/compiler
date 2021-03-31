## While Loops

### 类型
Lstart: evaluate condition
	jump to Lend if condition false
	statements
	jump to Lstart
Lend:

先解析条件， 然后判断是否跳转。

### New Tokens
T_WHILE
### Parsing the While Syntax
while 的条件解析与if相似， while 的 statement比if构造还少了一颗子树。

### Generic Code Generation
while 生成代码方式也与if 相似。

### int cgcompare_and_jump(int ASTop, int r1, int r2, int label)
作用：生成比较跳转汇编代码，
参数：ASTtop 是 因为目前限制了一部分判断条件。
     r1， 存储的第一个比较数，存在寄存器中
     label， 跳转地址， 也存储在寄存器中。

### Makefile
