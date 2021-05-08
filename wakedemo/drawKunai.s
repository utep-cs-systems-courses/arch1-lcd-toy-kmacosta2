	.arch msp430g2553
	
drawSpear:
	sub #10, r1
	mov.b #0, 0(r1) 	; for r
	mov.b #0, 1(r1) 	; for c
	mov.b r12, 2(r1) 	; u_char size
	mov.b r13, 3(r1) 	; offset_r
	mov.b r14, 4(r1) 	; offset_c

top:
	cmp 0(r1), 2(r1)	; size - r
	jnc outer
	mov 2(r1), 5(r1)	; T5 = size
	sub 0(r1), 5(r1)	; T5 -= r

secondTop:
	cmp 1(r1), 5(r1)	; T5 - c
	jnc secondOut

	mov.b 0(r1), 6(r1) 	; T1 = r
	mov.b 1(r1), 7(r1)	; T2 = c
	mov.b 8(r1), 3(r1)	; T3 = offset_r
	sub.b 6(r1), 8(r1)	; T3 -= T1
	mov.b 9(r1), 4(r1)	; T4 = offset_c
	mov.b 9(r1), 7(r1)	; T4 -= T2
	call #drawPixel		; method call
	mov.b 3(r1), 8(r1)	; 
	add.b 6(r1), 8(r1)	; 
	call #drawPixel
	add.b #1, 1(r1)		; c++
	jmp secondTop

secondOut:
	add.b #1, 0(r1)		; r++
	jmp top

outer:				;resrvParameters
	
	call #drawEnd
	pop r0			;return
