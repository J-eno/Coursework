# Makefile_nasm   for  nasm  .asm   64 bit files
all: convert.out

convert.out: convert.asm # using printf
	nasm -g -f elf64 -l convert.lst  convert.asm
	gcc -m64 -o convert  convert.o
	./convert > convert.out
	cat convert.out


# add to  all:  name.out  of output file  for name.asm
# add group hello_64.out ...  changing name  "hello_64" to new name
# be sure to use "tab" in front of nasm, gcc, etc
