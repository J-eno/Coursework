# Makefile_nasm   for  nasm  .asm   64 bit files
all: plotc.out

plotc.out: plotc.asm # using printf
	nasm -g -f elf64 plotc.asm
	ld -o plotc plotc.o
	./plotc  > plotc.out
	cat plotc.out


# add to  all:  name.out  of output file  for name.asm
# add group hello_64.out ...  changing name  "hello_64" to new name
# be sure to use "tab" in front of nasm, gcc, etc
