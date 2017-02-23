int bambo()
{
	__asm
		{
			mov	ax, CONST0
			mov	k, ax
			mov	ax, CONST1
			mov	i, ax
			jmp	LAB0
	K_LAB1	mov	ax, i
			add	ax, 1
			mov	i, ax
	LAB0	mov	cx, CONST2
			sub	ax, cx
			jnc	L_LAB2
			mov	ax, k
			add	ax, CONST3
			mov	MDREZ0, ax
			mov	ax, MDREZ0
			mov	k, ax
			JMP	K_LAB1
	L_LAB2	NOP


			MDREZ0	DWORD	0

			CONST0	DWORD	0
			CONST1	DWORD	0
			CONST2	DWORD	20
			CONST3	DWORD	5
	}
}
