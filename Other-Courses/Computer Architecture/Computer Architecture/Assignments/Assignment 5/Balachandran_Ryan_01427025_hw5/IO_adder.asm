main:		loco result:		; load the addr. of the result to
		push			; get back from AddInput
		call addinp:		; call the function
		halt
result:		0
addinp:		lodl 0			; get the return adr. and store it
		stod retadr:
		lodl 1			; get the result adr. and store it
		stod resadr:
		loco d5:		; initial setup - get pointer to
		stod pdig:		; last digit ready
start:		lodd on:		; turn xmtr on
		stod 4095
		call xbsywt:		; wait until xmtr ready
		loco prompt:		; load the prompt string's addr
nextw:		pshi			; push first 2 chars on stack
		addd c1:		; get next 2 chars in string
		stod pprmpt:
		pop
		jzer crnl:		; if null byte, done
		stod 4094		; put first char in xmtr
		push
		subd c255:		; get next char in 2 byte seq.
		jneg crnl:		; if null byte, done
		call sb:		; swap bytes in string
		insp 1
		push			; push new string on
		call xbsywt:		; wait for xmtr
		pop
		stod 4094		; print next char
		call xbsywt:		; wait for xmtr again
		lodd pprmpt:
		jump nextw:		; continue with next 2 chars in string

; This function outputs a carriage return and newline.
crnl:		lodd cr:		; print carriage return
		stod 4094		; write CR to output buffer
		call xbsywt:		; output carriage return
		lodd nl:		; print new line
		stod 4094		; write NL to output buffer
		call xbsywt:		; output newline
		lodd on:		
		stod 4093

bgndig:		call rbsywt:		; read in numerical input as a string
		lodd 4092
		subd numoff:		; subtract 48 from ascii char to get
		push			; numerical value, put on stack
nxtdig:		call rbsywt:
		lodd 4092		; get next 2 bytes
		stod nxtchr:
		subd nl:		; check for newline character
		jzer endnum:		; if nl, done reading number
		mult 10
		lodd nxtchr:		; convert next number
		subd numoff:
		addl 0
		stol 0
		jump nxtdig:		; loop until number is read
endnum:		lodd numcnt:
		subd c1:
		stod numcnt:
		jzer twoinp:
oneinp:		pop
		stod num1:
		jump start:
twoinp:		pop
		stod num2:
sumofd:		loco sumstr:		; load the string for sum of ints
nextw2:		pshi			; push first 2 chars on stack
		addd c1:		; get next 2 chars in string
		stod pprmpt:
		pop
		jzer crn12:		; if null byte, done
		stod 4094		; put first char in xmtr
		push
		subd c255:		; get next char in 2 byte seq.
		jneg crn12:		; if null byte, done
		call sb:		; swap bytes in string
		insp 1
		push			; push new string on
		call xbsywt:		; wait for xmtr
		pop
		stod 4094		; print next char
		call xbsywt:		; wait for xmtr again
		lodd pprmpt:
		jump nextw2:		; continue with next 2 chars in string
crn12:		lodd cr:		; print carriage return
		stod 4094
		call xbsywt:
		lodd nl:		; print new line
		stod 4094
		call xbsywt:
		lodd on:
		stod 4093
addnum:		lodd num1:		; retrieve num 1, ac = num1
		push			; put num 1 on stack, m[sp] = num1
		lodd num2:		; retrieve num 2, ac = num2
		addl 0			; num 2 (ac) + num 1 (sp), ac = num1 + num2
		stod rslt:		; store result in rslt:, rslt = ac (num1 + num2)
		jneg oflow:		; check for overflow
		pop			; get num 1 off stack - not needed
cnvrt:		lodd rslt:		; ready to store individ. digits of rslt:
		stod quot:		; start by putting rslt: into quot:
loopc:		loco 10			; loop for extracting digits from rslt:
		push			; set up for div (quot: / 10)
		lodd quot:
		push
		div			; do quot: / 10
		pop
		stod quot:		; pop and store quot:
		lodd pdig:		; store remainder into pdig's addr.
		popi
		insp 2			; okay to overwrite 2 nums used for div
		lodd pdig:		; get pdig to point to previous digit
		subd c1:
		stod pdig:
		lodd quot:		; if quotient != 0, loop again
		jnze loopc:		; else the num is separated into digits
prntr:		loco d1:		; start by making pdig point to the first
		stod pdig:		; char in the result string
		loco 6			; set loop counter up to 5 digits (+1)
		stod lpcnt:
loopp:		lodd lpcnt:		; loop for printing result
		subd c1:
		stod lpcnt:
		jzer donep:		; if lpcnt = 0, done printing result
		lodd pdig:
		pshi
		addd c1:		; set pdig up to point to next char
		stod pdig:
		lodd pchar:		; get digit into pchar
		pop
		jnze contin:		; if char != 0, move on
		push
		lodd igzer:		; we ignore only leading 0's
		jzer loopp:		; if it's leading, loop
		loco 1			; otherwise, set the flag so we
		stod igzer:		; no longer ignore 0's
		pop
contin:		push			; ensure we're no longer ignoring
		loco 1			; 0 characters if a non-zero has been
		stod igzer:		; found
		pop
		addd numoff:		; else, += 48 to make ascii value
		push			; push string on
		call xbsywt:		; wait for xmtr
		pop			; get string back
		stod 4094		; print char
		call xbsywt:		; wait for xmtr again
		jump loopp:		; and loop again
donep:		lodd cr:		; print carriage return
		stod 4094
		call xbsywt:
		lodd nl:		; print new line
		stod 4094
		call xbsywt:
		lodd on:
		stod 4093
		lodd rslt:		; success! store the result, load the
		push			; return addr, and set ac = 0
		lodd resadr:
		popi
		lodd retadr:
		push
		loco 0
		retn

; These are the transmitter / receiver functions for I/O
xbsywt:		lodd 4095		; Receiver address (input loop)
		subd mask:		; wait until transmitter
		jneg xbsywt:		; not busy
		retn
rbsywt:		lodd 4093		; Receiver address (input loop)
		subd mask:		; wait until receiver
		jneg rbsywt:		; not busy
		retn

sb:		loco 8			; load 8 (8 bits = 1 byte)
loop1:		jzer finish:		; loop until finished
		subd c1:		; subtract 1
		stod lpcnt:
		lodl 1			; load string on stack
		jneg add1:		; if left bit 1, make right bit 1
		addl 1			; else shift regularly
		stol 1
		lodd lpcnt:
		jump loop1:		; continue until left byte is on right
add1:		addl 1
		addd c1:		; re-shift in the 1 bit for a proper
		stol 1			; circular shift
		lodd lpcnt:
		jump loop1:
finish:		lodl 1			; done swapping bytes, return
		retn
oflow:		loco ofstr:		; load the string that says sum ints
nextw3:		pshi			; push first 2 chars on stack
		addd c1:		; get next 2 chars in string
		stod pprmpt:
		pop
		jzer crn13:		; if null byte, done
		stod 4094		; put first char in xmtr
		push
		subd c255:		; get next char in 2 byte seq.
		jneg crn13:		; if null byte, done
		call sb:		; swap bytes in string
		insp 1
		push			; push new string on
		call xbsywt:		; wait for xmtr
		pop
		stod 4094		; print next char
		call xbsywt:		; wait for xmtr again
		lodd pprmpt:		; load address of string positions
		jump nextw3:		; continue with next 2 chars in string
crn13:		lodd cr:		; print carriage return
		stod 4094
		call xbsywt:
		lodd nl:		; print new line
		stod 4094
		call xbsywt:
		lodd on:
		stod 4093
fail:		lodd retadr:		; failed from overflow. load
		push			; the return addr. and set ac = -1
		lodd cn1:
		retn

; *******************************************************
;   Variables
; *******************************************************

; NOTE:
; 4092 = input buffer
; 4093 = receiver address
; 4094 = output buffer
; 4095 = transmitter address

numoff:		48			; constant 48 (ASCII value for 0)
nxtchr:		0			; next character
lpcnt:		0			; loop counter
mask:		10			; mask
on:		8			; start transmitter
nl:		10			; ASCII value of Newline (nl)
cr:		13			; ASCII value of Carriage Return (cr)
c1:		1			; constant 1
cn1:		-1			; constant -1
c255:		255			; constant 255
pprmpt:		0			; string pointer
prompt:		"PLEASE ENTER AN INTEGER BETWEEN 1 AND 32767"
ofstr:		"OVERFLOW, NO SUM POSSIBLE"
sumstr:		"THE SUM OF THESE INTEGERS IS: "
d1:		0			; first digit of result
d2:		0			; second digit of result
d3:		0			; third digit of result
d4:		0			; fourth digit of result
d5:		0			; fifth digit of result
pdig:		0			; ptr to digits
num1:		0			; first number read in
num2:		0			; second number read in
rslt:		0			; result of adding two ints: num1 + num2
numcnt:		2			; to keep track of numbers read in
quot:		0			; temp. quotient when dividing
pchar:		0			; character to print
igzer:		0			; flag to ignore 0 chars or not
resadr:		0			; address to return the result in
retadr:		0			; address to return to
