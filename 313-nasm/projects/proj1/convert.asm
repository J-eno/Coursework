	;;  Declare needed C  functions
	        extern  printf	; the C function, to be called



		section .bss
dec_save:	resq	1
bin_save:	resq	1
abits:		resq	10
bbits:		resq	14
	
	        section .data	; Data section, initialized variables


fmt_char:	 db "%c",0	; no '\n' thus no 10
fmt_dig:	 db "%1ld",0	; print just one digit, e.g. 0 or 1
fmt_end:	 db 10, 0	; just end line

fmt_dec		db "126.375 is: ",10,0
fmt_bin		db "10101101.10111 is: ",10,0
	
dec1:	  	db '1', '2', '6', '.','3','7','5',0
bin1:	  	dq  1010110110111B 	; 10101101.10111 note where binary point should be


binaryPoints	dq	50000,25000,12500,6250,3125
result:		dq 	0	;holds results

	
	        section .text	; Code section.

	        global main	; the standard gcc entry point
main:				; the program label for the entry point
				;gets the first numbers before the decimal point
	        push    rbp	; set up stack frame, must be aligned

		mov	rdi,fmt_dec
		mov	rax,0
		call	printf
	        mov     rax, 0	     ; be safe, zero all rax
		mov	al, [dec1]; first byte into bottom of rax
		sub	rax, 48   ; chang character to digit
		imul 	rax,100
		mov	rsi, rax	     ; must go 64-bit to 64-bit
		mov	rax, 0		     ; no float
		

	        mov     rax, 0	; be safe, zero all rax
		mov	al, [dec1+1]	; next byte into bottom of rax
		sub	rax, 48		; change character digit to number
		imul	rax, 10
		add	rsi, rax	; must go 64-bit to 64-bit
		mov	rax, 0		; no float

		mov	rax,0
		mov	al,[dec1+2] ;next byte (4)
		sub	rax,48
		add	rsi, rax
		mov	[dec_save],rsi ;save the decimal number we have so far
		mov 	rax, 0

		mov 	rax, [dec_save]



	
		mov	rbx, 0
DtoB:					;Decimal to Binary
		mov	rdx, 0		;zero out rdx
		mov	rcx, 2		;move 2 into rcx
		div	rcx		;divide rax by rcx
					;remainder goes in rdx

		mov	[abits+rbx*8],rdx ;move the remainder into array abits
		mov 	rsi,[abits+rbx*8]
		
		mov	[result],rax ;move the result of the div into result
		mov 	rax, 0
	
	        mov	rax, [result]
		add	rbx, 1*8
		cmp 	qword [result], 0
		jg 	DtoB
	
		mov 	rbx, 6*8

printBeforeBP:			;print binary numbers before point
		mov 	rdi,fmt_dig
		mov	rax,[abits+rbx*8]
		mov	rsi,rax
		mov	rax,0
		call	printf
		sub 	rbx,8
		cmp	rbx,0
		jge	printBeforeBP
printBP:			;print point
	
		mov	rdi,fmt_char
		mov	rax,[dec1+3]
		mov	rsi,rax
		mov	rax,0
		call	printf


getAfterBP:			;get the rest of the decimal number
	        mov	byte [dec_save], 0
	        mov     al, [dec1+4]	 ; first byte into bottom of rax
	        sub     rax, 48	   	; chang character to digit
	        imul    rax,100
        	mov     rsi, rax ; must go 64-bit to 64-bit
	        mov     rax, 0	 ; no float

		
	        
                mov     al, [dec1+5] ; next byte into bottom of rax
        	sub     rax, 48	     ; change character digit to number
	        imul    rax, 10
	        add     rsi, rax ; must go 64-bit to 64-bit
	        mov     rax, 0	 ; no float

		

	        mov     al,[dec1+6] ;next byte (4)
	        sub     rax,48
	        add     rsi, rax
	        mov     [dec_save],rsi ;save the decimal number we have so far



		mov	rax, [dec_save]
		mov	qword [result],0
		mov	rbx, 3
	
DtoB2:
	;print first bit after point
		mov     rdi,fmt_dig
		mov     rdx, 0		;zero our rdx
		mov	rcx,500		;put 500 into rcx
		idiv	rcx		;divide by the 500
		mov     [result],rdx	;remainder of 375/500 is 375
	
	;; print stuff goes here
		mov 	rsi,rax
		mov	rax,0
		call	printf
	
		mov	rax, [result]   ;move remainder into rax

		mov	rdx,0
		mov	rcx,5
		idiv	rcx		;divide 375 by 5 to get 75
	
	;;print second bit after point - rax == 75
				
		mov	rdi,fmt_dig
		mov	rdx,0
		mov	rcx,50
		idiv	rcx		;divide 75 by 50
					;gives us remainder of 25
					;we need 5
		mov	[result],rdx

		mov	rsi,rax
		mov	rax,0
		call	printf

	
		mov	rax,[result]
		mov	rdx,0
		mov	rcx,5
		idiv	rcx
		
	
	;; print 3rd bit after the point - rax == 5
		mov	rdi,fmt_dig
		mov	rdx,0
		mov	rcx,5
		idiv	rcx

		mov	rsi,rax
		mov	rax,0
		call	printf

		mov     rdi,fmt_end	; print end of line
		mov     rax, 0 		; no float
		call    printf
	

		mov     rdi,fmt_end		; print end of line
		mov     rax, 0 ; no float
		call    printf

		mov     rdi,fmt_bin ; print binary message
		mov     rax, 0 ; no float
		call    printf
	
	
printBinaryWhole:	
		mov	rdi,fmt_dig
		mov	rax,[bin1]
		shr	rax,5
		mov	rsi,rax
		mov	rax,0
		call	printf

		
fracToArray:
		mov	qword[bbits],1
		mov     qword[bbits+8],0
		mov     qword[bbits+16],1
		mov     qword[bbits+24],1
		mov     qword[bbits+32],1
		mov	rbx,0
		mov	qword[result],0



printBP2:			;print point

	                mov     rdi,fmt_char
	                mov     rax,[dec1+3]
	                mov     rsi,rax
	                mov     rax,0
	                call    printf
	

binToDec:
		mov	rdi,fmt_dig
		mov	rax,[bbits +rbx]
		imul	rax,[binaryPoints +rbx]
		add	[result],rax
		add	rbx,8
		cmp	rbx,5*8
		jle	binToDec

		mov	rsi,[result]
		mov	rax,0
		call	printf
		





		mov     rdi,fmt_end     	; print end of line
		mov     rax, 0 ; no float
		call    printf
	
	        pop     rbp	; restore stack

	        mov     rax,0	; normal, no error, return value
	        ret		; return

	