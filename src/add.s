	mov r1, #1
	mov r2, #2
	add r2, r2, r1
	ldr r3, =WRITE_VALUE
	ldr r4, =WRITE_TARGET
	str r3, [r4, #0]
	bkpt #0

	.equ WRITE_VALUE,	0xDEADBEEF
	.equ WRITE_TARGET, 	0x20000000
	