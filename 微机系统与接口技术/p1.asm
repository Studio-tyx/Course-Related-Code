;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	author:tyx
;	time:2021-06-07 16:51
;	description:code for practice-1
;					input N, calculate N!, and output with hex code
;					if input 0, return
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
data segment
hex		db '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','H'
endl	db 0dh,0ah,'$'
data ends
code segment		;code segment
	assume cs:code,ds:data
start:	
	mov ax,data
	mov ds,ax	;data segment

	mov ah,01h	;input N
	int 21h
	
	sub al,30h	;transfer N from ASCII to number
	mov ah,0	;reset ah
	mov cx,ax	;initial ax<-N
	dec cx		;initial cx<-N-1, because ax already equals to N
	cmp cx,0
	jz stack0	;input 1, skip ax*cx(cx==0)
	jl output2	;input 0 or negative, jump to end of process
	
multiple:
	mul cx			;ax<-ax*cx
	loop multiple	;loop to calculate N!

stack0:
	mov bx,10h		;initial bx<-16, for the comparation
	
	;after calculate, the result of N! is in ax
	;output algorithm:
	;	compare with 0, if not equals to 0: first divide by 16 
	;		the remained: push to stack
	;		the quotient: next to be calculate
stack1:
	cmp ax,0	
	jz endproc	;end of loop
	mov dx,0	;reset dx
	div bx		;divide by 16
	push dx		;the remained: push to stack
	inc cx		;count for stack
	jmp stack1	;the quotient: next to be calculate
	
endproc:
	mov dx,offset endl	;output '\r\n'
	mov ah,09h
	int 21h
	
	mov bx,offset hex	;prepare for output hex code
	
output1:
	pop dx		;the remained: push to stack
	mov ax,dx	;prepare for xlat
	xlat		;AL¡û[BX£«AL]
	mov dx,ax	;prepare for output(make dx as input parameter)
	mov ah,02h	;output hex code
	int 21h
	loop output1
	
	mov ax,16	;output 'H'
	xlat
	mov dx,ax
	mov ah,02h
	int 21h

output2:
	mov ax,4c00h
	int 21h		;end of process
code ends
    end start	;end of assemble
