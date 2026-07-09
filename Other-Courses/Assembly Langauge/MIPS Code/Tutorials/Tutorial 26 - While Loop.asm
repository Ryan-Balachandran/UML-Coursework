		.data
message:	.asciiz "After while loop is done"
space:		.asciiz ", "

		.text
main:
	addi $t0, $0, 0		# i = 0
	
	while:
		bgt $t0, 10, exit	# Branch if $t0 > 10, goto exit
		jal printNumber		# jump to printNumber
		addi $t0, $t0, 1	# $t0 = $t0 + 1
		
		j while			# jump unconditionally	
	
	exit:
		li $v0, 4		# Service code 4 to print a string
		la $a0, message		# $a0 = message
		syscall
		
		# Tell the system that this is the end of main
		li $v0, 10		# Service code 10 to exit program
		syscall			# Exit 
		
	printNumber:
		li $v0, 1		# Service code 4 to print an integer
		add $a0, $t0, $0	# $a0 = $t0 + $0
		syscall			# Print integer
		
		li $v0, 4		# Service code 4 to print a string
		la $a0, space		# $a0 = space
		syscall			# Print string
		
		jr $ra 			# jump and return to return address
