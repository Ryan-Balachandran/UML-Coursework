nextw:		pshi
		addd c1a:
		stod pprmpt:
		pop
		jzer crnl:
		stod 4094
		push
		subd c255a:
		jneg crnl:
		call sb:
		insp 1
		push
		call xbsywt:
		pop
		stod 4094
		call xbsywt:
		lodd pprmpt:
		jump nextw:
crnl:		lodd cra:
		stod 4094
		call xbsywt:
		lodd nla:
		stod 4094
		call xbsywt:
		lodd on2:
		stod 4093
		call bgndig:
cnvrt:		lodd rslt:
		stod quot:
loopc:		loco 10
		push
		lodd quot:
		push
		div
		pop
		stod quot:
		lodd pdig:
		popi
		insp 2
		lodd pdig:
		subd c1a:
		stod pdig:
		lodd quot:
		jnze loopc:
prntr:		loco d1:
		stod pdig:
		loco 6
		stod lpcnt:
loopp:		lodd lpcnt:
		subd c1a:
		stod lpcnt:
		jzer donep:
		lodd pdig:
		pshi
		addd c1a:
		stod pdig:
		lodd pchar:
		pop
		jnze contin:
		push
		lodd igzer:
		jzer loopp:
		loco 1
		stod igzer:
		pop
contin:		push
		loco 1
		stod igzer:
		pop
		addd numoff:
		push
		call xbsywt:
		pop
		stod 4094
		call xbsywt:
		jump loopp:
donep:		lodd cra:
		stod 4094
		call xbsywt:
		lodd nla:
		stod 4094
		call xbsywt:
		lodd on2:
		stod 4093
		lodd rslt:
		push
		lodd resadr:
		popi
		lodd retadr:
		push
		loco 0
		retn
