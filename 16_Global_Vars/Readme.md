## 定义变量
合并 函数变量 和 值变量


* 同时定义多个同类型变量

* BNF

 global_declarations : global_declarations 
      | global_declaration global_declarations
      ;

 global_declaration: function_declaration | var_declaration ;

 function_declaration: type identifier '(' ')' compound_statement   ;

 var_declaration: type identifier_list ';'  ;

 type: type_keyword opt_pointer  ;
 
 type_keyword: 'void' | 'char' | 'int' | 'long'  ;
 
 opt_pointer: <empty> | '*' opt_pointer  ;
 
 identifier_list: identifier | identifier ',' identifier_list ;

 * new tokens
 T_COMMA - ','
  
* delc.c
转换这个BNF 到global_declarations()
修改var_declarations() 为了实现多变量定义，加入循环，并且为该函数添加一个参数type


* main.c
把这个全局变量添加到main函数中




