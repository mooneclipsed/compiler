## 变量

1. 定义变量
2. 用变量来存储值
3. 分配变量值

## Symbol Table
可以向表中添加更多的全局变量
```
// Symbol table structure
struct symtable {
  char *name;                   // Name of a symbol
};
```

用一个数组来存储全局变量名.查找的时候效率有点拉胯emmm。

```
#define NSYMBOLS        1024            // Number of symbol table entries
extern_ struct symtable Gsym[NSYMBOLS]; // Global symbol table
static int Globs = 0;                   // Position of next free global symbol slot
```

## 新的符号
'int', known as T_INT
'=', known as T_EQUALS
identifier names, known as T_IDENT

## assign to variables
修改primary()
```
  case T_IDENT:
    // Check that this identifier exists
    id = findglob(Text);
    if (id == -1)
      fatals("Unknown variable", Text);

    // Make a leaf AST node for it
    n = mkastleaf(A_IDENT, id);
    break;
```




