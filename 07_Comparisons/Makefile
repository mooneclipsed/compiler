SRCS= cg.c decl.c expr.c gen.c main.c misc.c scan.c stmt.c sym.c tree.c
comp1: $(SRCS)
	gcc -o comp1 -g $(SRCS)

clean:
	rm -f comp1 *.o *.s out

test: comp1 input03
	./comp1 input03
	gcc -o out -m64 out.s
	./out
