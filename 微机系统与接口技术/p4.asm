;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	author: tyx
;	create time: 2021-06-14 09:20
;	finish time: 2021-06-14 10:13
;	summary: code for practice-4
;	description: 8254 count and 8259 interrupt are used together. 
;		Pulse signal is used to simulate interrupt request.
;		A capital letter is displayed on the screen every 4 times of pressing KK1.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
A8254 EQU 06C0H		;channel 0
B8254 EQU 06C2H		;channel 1
C8254 EQU 06C4H		;channel 2
CON8254 EQU 06C6H	;control port
sstack SEGMENT STACK 
DW 32 DUP(?) 
sstack ENDS
code segment
	assume cs:code,ss:sstack
start:
	push ds
	mov ax,0
	mov ds,ax		;change data segment
	mov ax,offset IRQ7
	mov si,003ch	;IRQ7 address: 0x3c~0x3f
	mov [si],ax
	mov ax,cs
	mov si,003eh
	mov [si],ax
	cli
	pop ds
	
	mov cx,41h

	mov al,11h	;0001 0001: have ICW4; not single;
	out 20h,al	;ICW1
	mov al,08h	;0000 1000: interrupt number high->00000
	out 21h,al	;ICW2
	mov al,04h	;0000 0100: IR2 has the slave
	out 21h,al	;ICW3
	mov al,01h	;0000 0001: not end automatically; 8086
	out 21h,al	;ICW4
	mov al,6fh	;0110 1111: allow IR7 and IR4
	out 21h,al	;OCW1
	
	;8254
	mov dx,CON8254
	mov al,10h	;0001 0000: counter 0; only R/W lower byte; 
	out dx,al	;control
	mov dx,A8254;channel 0
	mov al,03h	;initial count
	out dx,al
	sti

AA1:
	jmp AA1		;dead cycle

IRQ7:
	mov dx,A8254	;channel 0
	mov al,03h		;reset count = 4
	out dx,al
	;mov ax,0141h
	
	mov dx,cx
	mov ah,02
	int 21h
	inc cx
	
	
	mov al,20h		;0010 0000: EOP
	out 20h,al		;send EOP
	iret
	
	code ends
end start