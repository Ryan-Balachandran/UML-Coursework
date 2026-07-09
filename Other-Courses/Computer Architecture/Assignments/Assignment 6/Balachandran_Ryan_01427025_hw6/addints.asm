addnum:		lodd num1:
		push
		lodd num2:
		addl 0
		stod rslt:
		jneg oflow:
		pop
		call cnvrt: