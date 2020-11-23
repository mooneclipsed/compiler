* 为函数添加一个返回值。

* 函数的BNF：
function_call: identifier '(' expression ')';

* 区分变量名与函数名
   x= fred + jim;
   x= fred(5) + jim;

   fred = 2;
   fred(18);

* Parsing a Return Statement
