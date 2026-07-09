		.data
inBuf:		.space 	80		# inBuf array, store input line - maximum of 80 characters
outBuf:		.space 	80		# outBuf array, store character types to match input - maximum of 80 characters		
prompt:		.asciiz "Enter a new input string: "
newLine:	.asciiz "\n"

		.text		
newline:
	jal 	getline				# retrieve input
	
	lb 	$t0, inBuf($0)			# $t1 = first element in inBuf array
	beq 	$t0, '#', exit			# branch if $t0 = #, goto exit
	
	li 	$t0, 0				# i = 0, index of inBuf
		
nextChar:
	bge 	$t0, 80, dump 			# Branch if $t0 >= 80, goto dump	
	lb	$t9, inBuf($t0)			# load first byte into register $t9 for search key
		
	jal 	lin_search			# jump to linear search function
	
	beq 	$s7, 5, skip_spaces		# branch if char is a space, goto substitute_spaces
	addi 	$s7, $s7, 0x30			# modify char type to ascii value
	
store_type:
	sb 	$s7, outBuf($t0)		# store ascii value in outBuf[i]
	
	beq 	$t9, '#', dump			# branch if $t9 = #, goto dump
	addi 	$t0, $t0, 1			# i++
	
	b 	nextChar			# branch to nextchar	

##########################################
# Linear_search()
#	$t0: index i of inBuf
#	$s0: index j into Tabchar
#	$t9: key char to search
#	$s5: char in Tabchar entry
#	$s7: char type in Tabchar
#########################################
lin_search:
	la 	$s5, Tabchar		# base address of Tabchar
	li 	$s0, 0			# j = 0
	
compare:
	beq 	$s0, 0x5c, done 	# branch to done if no match is found in Tabchar
	lb 	$s7, ($s5)		# current character in Tabchar[i]
	
	beq 	$s7, $t9, match		# branch if $s7 = $t9, goto match
	
	addi 	$s5, $s5, 8		# skip character and character type to get to next character
	addi 	$s0, $s0, 1		# j++

	b 	compare
	
match:
	addi 	$s5, $s5, 4		# if match is found, add 4 to address of Tabchar to get char type
	lw 	$s7, ($s5)		# Store value in $s7
		
done:
	jr 	$ra

skip_spaces:	
	li 	$s7, 0x20		# replace character type 5 with spaces
	b 	store_type
	
dump:
	jal 	printBuffers		# jump and link to printBuffers
	jal 	clearBuffers		# jump and link to clearBuffers
	
	la 	$a0, newLine		# Prompt to enter a new line
	li 	$v0, 4			# Service code 4 to print a string
	syscall				# Print newLine
	
	b 	newline			# read another string 	
	
# End of program
exit:
	li 	$v0, 10			# Service code 10 to exit program
	syscall				# Exit

##########################################
# printBuffers()
# 	- print input and output buffers
##########################################
printBuffers:
	la 	$a0, inBuf		# $a0 = inBuf
	li 	$v0, 4			# Service code 4 to print a string
	syscall				# Print string
	
	la 	$a0, outBuf		# $a0 = outBuf
	li 	$v0, 4			# Service code 4 to print a string
	syscall				# Print string
	
	jr $ra

##########################################
# ClearBuffers()
# 	- clear input and output buffers
##########################################
clearBuffers:
	li 	$t0, 0			# i = 0
		
loop:	
	bge 	$t0, 80, cleared	# while (i < 80) {
	sb 	$0, inBuf($t0)   	# 	inBuf[i] = 0;
	sb	$0, outBuf($t0)		#	outBuf[i] = 0;
	addi 	$t0, $t0, 1		# 	i++	
					# }
	b 	loop			# branch back to loop
	
cleared:
	jr 	$ra

#################################
# getline()
#	$a0 - read input
#	$a1 - 80 character limit
##################################
getline:
	la 	$a0, prompt		# Prompt to enter a new line
	li 	$v0, 4			# Service code 4 to print a string
	syscall				# Print message
	
	la 	$a0, inBuf		# Load address of inBuf array into $a0
	li 	$a1, 80			# limit of characters to be read
	li 	$v0, 8			# Service code 8 to read a string
	syscall				# Get input
	
	jr 	$ra			# return to function call

# Array to compare each character against and to get the code to print out.
		.data
Tabchar:	.word 0x0a, 6		# LF
		.word ' ', 5
		.word '#', 6
		.word '$', 4
		.word '(', 4
		.word ')', 4
		.word '*', 3
		.word '+', 3
		.word ',', 4
		.word '-', 3
		.word '.', 4
		.word '/', 3
		
		.word '0', 1
		.word '1', 1
		.word '2', 1
		.word '3', 1
		.word '4', 1
		.word '5', 1
		.word '6', 1
		.word '7', 1
		.word '8', 1
		.word '9', 1
		
		.word ':', 4
		
		.word 'A', 2
		.word 'B', 2
		.word 'C', 2
		.word 'D', 2
		.word 'E', 2
		.word 'F', 2
		.word 'G', 2
		.word 'H', 2
		.word 'I', 2
		.word 'J', 2
		.word 'K', 2
		.word 'L', 2
		.word 'M', 2
		.word 'N', 2
		.word 'O', 2
		.word 'P', 2
		.word 'Q', 2
		.word 'R', 2
		.word 'S', 2
		.word 'T', 2
		.word 'U', 2
		.word 'V', 2
		.word 'W', 2
		.word 'X', 2
		.word 'Y', 2
		.word 'Z', 2
		 
		.word 'a', 2
		.word 'b', 2
		.word 'c', 2
		.word 'd', 2
		.word 'e', 2
		.word 'f', 2
		.word 'g', 2
		.word 'h', 2
		.word 'i', 2
		.word 'j', 2
		.word 'k', 2
		.word 'l', 2
		.word 'm', 2
		.word 'n', 2
		.word 'o', 2
		.word 'p', 2
		.word 'q', 2
		.word 'r', 2
		.word 's', 2
		.word 't', 2
		.word 'u', 2
		.word 'v', 2
		.word 'w', 2
		.word 'x', 2
		.word 'y', 2
		.word 'z', 2
		
		.word 0x5c, -1		# if you '\' as the end-of-table symbol
		
