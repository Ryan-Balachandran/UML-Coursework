		.data
message:	.asciiz "Hi, how are you?"

		.text
main:
	addi $s0, $0, 14		# $s0 = $0 + 14
	addi $s1, $0, 10		# $s1 = $0 + 10
	
	# pseudo instruction
	bgt $s0, $s1, displayHi		# Branch if $s0 > $s1, goto displayHi
	
	########################################################
	
	addi $s0, $0, 10		# $s0 = $0 + 10
	addi $s1, $0, 14		# $s1 = $0 + 14
	
	# pseudo instruction
	blt $s0, $s1, displayHi		# Branch if $s0 < $s1, goto displayHi
	
	########################################################
	
	addi $s0, $0, 10		# $s0 = $0 + 10
	
	# pseudo instruction
	bgtz $s0, displayHi		# Branch if $s0 > 0, goto displayHi
	
	########################################################
	
	addi $s0, $0, -10		# $s0 = $0 + -10
	
	# pseudo instruction
	bgtz $s0, $0, displayHi		# Branch if $s0 > 0, goto displayHi
	
	########################################################

	# Tell the system that this is the end of main
	li $v0, 10		# Service code 10 to exit program
	syscall			# Exit 

# Only printed if $s0 > $s1
displayHi:
	li $v0, 4		# Service code 4 to print a string
	la $a0, message		# $a0 = message
	syscall			# Print string
