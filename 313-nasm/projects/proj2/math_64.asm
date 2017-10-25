; math_64.asm  a direct coding of  math_64.c  (included as comments)
;// math_64.c  compute dot and cross product of two vectors
;double dot(long int n, double x[], double y[])
;{
;  double sum = 0.0;
;  long int i;
;  for(i=0; i<n; i++) sum = x[i]*y[i];
;  return sum;
;} // end dot
;
;void cross(long int n, double x[], double y[], double z[])
;{
;  double sign = 1.0;
;  long int m, j, k;
;  for(m=0; m<n; m++) // answer
;  {
;    z[m] = 0.0;
;    for(j=0; j<n; j++) // column
;    {
;      k = j+m;
;      if(k>=n) k = k-n;
;      z[m] = z[m] + x[j]*y[k];
;    } // end j
;    z[m] = sign*z[m];
;    sign = -sign;
;  } // end m
;} // end cross

        extern printf

	section .data
dfmt1:	db "dot n=%ld", 10, 0
cfmt1:	db "cross n=%ld", 10, 0
dfmt2:	db "x[1]=%e", 10, 0
sum:	dq 0.0
sign:	dq 1.0
zero:	dq 0.0
m:	dq 0
j:	dq 0
k:	dq 0
	
	section .bss
n:	resq 1			; value of n
x:	resq 1			; address of x array
y:	resq 1			; address of y array
z:	resq 1			; address of z array
	
	section .text
	global dot		; dot(n,x,y)
dot:
        push	rbp		; save rbp
	
	mov	[n],rdi		; save value of n
	mov	[x],rsi		; save address of x array
	mov	[y],rdx		; save address of y array
	
	mov	rdi, dfmt1
	mov	rsi, [n]        ; print value of n
	mov	rax, 0
	call	printf

	mov	rdi, dfmt2
	mov	rbx, [x]	; address of x[0]
	movq	xmm0, qword [rbx+8] ; address of x[1]
	mov	rax, 1
	call	printf
	
	; compute dot product and put function result in  xmm0

	mov	rax,[x]		; address of x[0] in rax
	mov	rbx,[y]	 	; address of y[0] in rbx
	mov     r8,0         	;counter
	
; this needs to loop [n] times
dotLoop:	
	fld	qword [rax +r8]	; value of x[0] on FP stack
	fmul	qword [rbx +r8]  	; add value of y[0] to FP stack
	fadd	qword [sum]	; accumulate sum
	fstp    qword [sum] 	; save sum
	add	r8,8		;decrement
	cmp	r8,4*8
	jl	dotLoop

	movq	xmm0, qword [sum]	; return value of sum
        pop	rbp
        ret			; return
; end dot

	global cross		; cross(n,x,y,z)
cross:
        push	rbp		; save rbp

	mov	[n],rdi		; save address of n
	mov	[x],rsi		; save address of x
	mov	[y],rdx		; save address of y
	mov	[z],rcx		; save address of z
	
	mov	rdi, cfmt1
	mov	rsi, [n]	; print value of n
	mov	rax, 0
	call	printf

	; compute cross product and put result in z array
mLoop:	
	mov r8,[m]   		; loop m=0 .. m<n
	mov r9,[j]   		; inner loop j=0 .. j<n
	mov r10,[k]  		; computed if ...
	
	mov     rax,[x]         ; address of x[0] in rax
	mov     rbx,[y]		; address of y[0] in rbx
		

	fld  qword [zero]	;value of zero loaded
	mov  rcx, [z]		; z: has address of callers z array
	fstp qword [rcx+r8*8] 	; can not say  qword [[z]]
				; add 8 to rax for next value


jLoop:
	mov r11,r9 		;j to rdx
	add r11,r8		;j + m
				;k = r11 right now
ifCase:	
	cmp r11,[n]		;compare value in r11 to n
	jge true1

	jmp jLoopCont
true1:
	sub r11,[n]		;k - n
	jmp jLoopCont
	
jLoopCont:
	mov r10,r11		;move r11 into r10
	fld  qword [rax+r9*8]  	; x[j]
	fmul qword [rbx+r10*8] 	; x[j]*y[k]
	fadd qword [rcx+r8*8]  	; z[m]+x[j]*y[k]
	fstp qword [rcx+r8*8]  	; z[m] = z[m]+x[j]*y[k]

	add r9, 1
	mov [j],r9
	cmp     r9,[n]
	jl      jLoop

mLoopCont:

	fld qword [rcx+r8*8]	;z[m]
	fmul qword [sign]	;z[m]*sign
	fstp qword [rcx+r8*8]	;z[m] = z[m]*sign

	
	fld  qword [sign]
	fchs
	fstp qword [sign]	; sign = -sign

	add r8, 1
	mov [m],r8
	mov qword [j],0
	cmp r8, [n]
	jl  mLoop
	
	pop	rbp
        ret			; return
; end cross
