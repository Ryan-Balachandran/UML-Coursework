		.data
message:	.asciiz "The number is less than the other."

		.text
main:
	# slt - set if less than
	# Compare two numbers, if first is less than second
	# true if first is less than
	# false if otherwise

	addi $t0, $0, 1			# $t0 = $0 + 1
	addi $t1, $0, 200		# $t1 = $0 + 200
	
	#addi $t0, $0, 400		# $t0 = $0 + 400
	#addi $t1, $0, 200		# $t1 = $0 + 200

	slt $s0, $t0, $t1		# if $t0 < $t1, $s0 = 1, else $s0 = 0
	bne $s0, $0, printMessage	# Branch if $s0 != $0, goto printMessage

	# Tell the system that this is the end of main
	li $v0, 10		# Service code 10 to exit program
	syscall			# Exit 

printMessage: 
	li $v0, 4		# Service code 4 to print a string
	la $a0, message		# $a0 = message
	syscall			# Print message
