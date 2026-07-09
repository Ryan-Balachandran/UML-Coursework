bgndig:		call rbsywt:
		lodd 4092
		subd numoff1:
		push
nxtdig:		call rbsywt:
		lodd 4092
		stod nxtchr:
		subd nlb:
		jzer endnum:
		mult 10
		lodd nxtchr:
		subd numoff1:
		addl 0
		stol 0
		jump nxtdig:
