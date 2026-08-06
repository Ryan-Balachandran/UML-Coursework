main:		loco result:
		push
		call addinp:
		halt
result:		0
addinp:		lodl 0
		stod retadr:
		lodl 1
		stod resadr:
		loco d5:
		stod pdig:
start:		lodd on1:
		stod 4095
		call xbsywt:
		loco prompt:
		call nextw: