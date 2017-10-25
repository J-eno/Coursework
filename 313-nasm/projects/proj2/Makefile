# Makefile_nasm   for  nasm  .asm   64 bit files
all: test_math_64.out

test_math_64.out: math_64.asm # using printf
	nasm -f elf64 math_64.asm
	gcc -g3 -m64 -o test_math_64  test_math_64.c math_64.o
	./test_math_64 > test_math_64.out
	cat test_math_64.out


# add to  all:  name.out  of output file  for name.asm
# add group hello_64.out ...  changing name  "hello_64" to new name
# be sure to use "tab" in front of nasm, gcc, etc
