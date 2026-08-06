		.data
message:	.asciiz "The numbers are equal."
message2:	.asciiz "The numbers are different."

		.text
main:
	addi $t0, $0, 5				# $t0 = $0 + 5
	addi $t1, $0, 20			# $t1 = $0 + 20
	
	beq $t0, $t1, numbersEqual		# Branch if $t0 = $t1, goto numbersEqual
	bne $t0, $t1, numbersDifferent		# Branch if $t0 != $t1, goto numbersDifferent
	
	b numbersDifferent			# Jump to function unconditionally

	# Tell the system that this is the end of main
	li $v0, 10				# Service code 10 to exit program
	syscall					# Exit 

numbersEqual:
	li $v0, 4		# Service code 4 to print a string
	la $a0, message		# $a0 = message
	syscall			# Print string
	
numbersDifferent:
	li $v0, 4		# Service code 4 to print a string
	la $a0, message2	# $a0 = message2
	syscall			# Print string
