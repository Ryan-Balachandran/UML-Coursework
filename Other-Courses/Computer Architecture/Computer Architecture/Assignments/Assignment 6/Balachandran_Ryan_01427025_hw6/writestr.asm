endnum:		lodd numcnt:
		subd c1b:
		stod numcnt:
		jzer twoinp:
oneinp:		pop
		stod num1:
		jump start:
twoinp:		pop
		stod num2:
sumofd:		loco sumstr:
nextw2:		pshi
		addd c1b:
		stod pprmpt:
		pop
		jzer crn12:
		stod 4094
		push
		subd c255b:
		jneg crn12:
		call sb:
		insp 1
		push
		call xbsywt:
		pop
		stod 4094
		call xbsywt:
		lodd pprmpt:
		jump nextw2:
crn12:		lodd crb:
		stod 4094
		call xbsywt:
		lodd nlc:
		stod 4094
		call xbsywt:
		lodd on3:
		stod 4093
		call addnum:
oflow:		loco ofstr:
nextw3:		pshi
		addd c1b:
		stod pprmpt:
		pop
		jzer crn13:
		stod 4094
		push
		subd c255b:
		jneg crn13:
		call sb:
		insp 1
		push
		call xbsywt:
		pop
		stod 4094
		call xbsywt:
		lodd pprmpt:
		jump nextw3:
crn13:		lodd crb:
		stod 4094
		call xbsywt:
		lodd nlc:
		stod 4094
		call xbsywt:
		lodd on3:
		stod 4093
fail:		lodd retadr:
		push
		lodd cn1:
		retn