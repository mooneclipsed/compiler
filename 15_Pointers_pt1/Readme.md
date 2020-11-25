* 定义指针
定义指针变量
为指针分配一个地址
解引用


* 添加的Tokens
'&' and '&&'
T_AMPER,  T_LOGAND

'*'  定义指针
'&'  解引用

* 前缀操作符'&', '*'

 prefix_expression: primary
     | '*' prefix_expression
     | '&' prefix_expression
     ;


* 新的AST types
A_DEREF：解引用子节点的指针
A_ADDR： 指针地址