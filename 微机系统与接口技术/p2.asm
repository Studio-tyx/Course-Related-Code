;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	author:tyx
;	time:2021-06-06 20:32
;	description:code for practice-2
;					write 1000H-100FH to 8000H:1000H
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
code segment 
	assume cs:code
start:	
	push ds			;protect data segment
	
	mov ax,8000h	;initial ds
	mov ds,ax
	
	mov ax,1000h	;the number to be wrote
	mov bx,1000h	;address
	mov cx,16		;count
	
write:
	mov [bx],al		;write
	inc bx
	mov [bx],ah
	inc bx		
	inc ax			;number++
	loop write
	
	pop ds
	mov ax,4c00h
	int 21h		;end of process
code ends
    end start	;end of assemble
