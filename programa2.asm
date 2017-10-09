segment .data
	msg_div_cero db "FATAL ERROR. DIVISION POR CERO", 0
segment .bss
	__esp resd 1
	_b1 resb 1
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, print_string, scan_boolean, print_boolean
	extern print_endofline, print_blank
	extern alfa_malloc, alfa_free, ld_float
; ------------------------
; PROCEDIMIENTO PRINCIPAL
; ------------------------
main: 
; GUARDA DE PUNTERO DE PILA
	mov dword [__esp] , esp
	push dword _b1
	call scan_boolean
	add esp, 4
	push dword _b1
	pop dword eax
	mov ecx, [eax]
	mov eax, ecx
	cmp eax, 0
	je uno_0
	push dword 0
	jmp terminar_0
uno_0:
	push dword 1
terminar_0:
	call print_boolean
	call print_endofline
	add esp, 4
	push dword _b1
	pop dword eax
	mov ecx, [eax]
	mov eax, ecx
	cmp eax, 0
	je uno_1
	push dword 0
	jmp terminar_1
uno_1:
	push dword 1
terminar_1:
	pop dword eax
	cmp eax, 0
	je uno_2
	push dword 0
	jmp terminar_2
uno_2:
	push dword 1
terminar_2:
	call print_boolean
	call print_endofline
	add esp, 4
; RESTAURACION DE PUNTERO DE PILA
	mov dword esp, [__esp]
	ret
div_por_cero:
	push dword msg_div_cero
	call print_string
	mov dword esp, [__esp]
	ret
