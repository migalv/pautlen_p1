segment .data
	msg_div_cero db "FATAL ERROR. DIVISION POR CERO", 0
segment .bss
	__esp resd 1
	_x resd 1
	_y resd 1
	_z resd 1
	_b1 resb 1
	_j resd 1
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
	push dword _x
	call scan_int
	add esp, 4
	push dword _z
	call scan_int
	add esp, 4
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
	push dword _x
	pop dword eax
	mov ecx, [eax]
	mov eax, ecx
	mov ebx, eax
	sub eax, ebx
	sub eax, ebx
	push dword eax
	pop dword eax
	mov [_j], eax
	push dword _j
	pop dword eax
	mov ebx, [eax]
	push dword ebx
	call print_int
	call print_endofline
	add esp, 4
	push dword _x
	push dword _z
	pop dword ebx
	pop dword eax
	mov ecx, [eax]
	mov eax, ecx
	mov ecx, [ebx]
	mov ebx, ecx
	add eax, ebx
	push dword eax
	call print_int
	call print_endofline
	add esp, 4
	push dword _z
	pop dword eax
	mov ebx, [eax]
	push dword ebx
	call print_int
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
