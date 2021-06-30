;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	author: tyx
;	create time: 2021-06-14 09:04
;	finish time: 2021-06-14 09:20
;	description: code for practice-3
;					keep the light consistent with the switch state, 
;					flash when all "0", exit when all "1".
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
code segment
	assume cs:code
start:
	mov dx,0646h
	mov al,90h	;A:input, B:output, using mode 0
	out dx,al
AA1:
	mov dx,0640h
	in al,dx	;input the status of switch
	call delay
	mov dx,0642h	;output address
	cmp al,0	
	jz flash
	cmp al,0ffh	
	jz finish
	out dx,al	;keep the same output
	jmp AA1

flash:
	mov cx,8
loop_flash:
	mov al,0
	out dx,al
	call delay
	mov ax,00ffh
	out dx,al
	call delay
	loop loop_flash
	jmp AA1
	
delay:
	push cx
	mov cx,0ffffh	;loop 0ffffh times to delay
AA2:
	push ax
	pop ax
	loop AA2
	pop cx
	ret
	
finish:
	mov ax,4c00h
	int 21h		;end of process
	code ends
end start