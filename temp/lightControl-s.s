	.arch msp430g2553
	.p2align 1,0
	.text

jt:
	.word case_1
	.word case_2
	.word case_3
	.word def
	
	.global lightControl
	.extern P1OUT

lightControl:

	cmp #3, r12
	jhs def
	
	add r12, r12
	mov jt(r12), r0
	
case_1:	and #~65, &P1OUT	;Both LEDs OFF
	jmp end
	
case_2:	bis #64, &P1OUT 	;Green LED On Only
	and #~1, &P1OUT
	jmp end
	
case_3: and #~64, &P1OUT	;Red LED On Only
	bis #1, &P1OUT
	pop r0
	
def:	bis #65, &P1OUT 	;Both LEDs On
	jmp end
	
end:	pop r0
