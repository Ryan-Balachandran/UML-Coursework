		.data
myArray:	.word 100:3	# initialize 3 integers to 100
#myArray:	.word 5:3	# initialize 3 integers to 5
myArray:	.word 5:10	# initialize 10 integers to 5
newLine:	.asciiz "\n"
		.text

main:	
	# clear $t0 to 0
	addi $t0, $0, 0		# $t0 = $0 + 0

while:
	beq $t0, 12, exit	# Branch if at end of array - goto exit
	#beq $t0, 40, exit	# Modified when number of integers are 10 (10 integers * 4 bytes)
	lw $t6, myArray($t0)	# load array element into $t6
	
	addi $t0, $t0, 4	# increment index by 1 (4 bytes)
	
	# Print current number
	li $v0, 1		# Service code 1 to print an integer
	move $a0, $t6		# $a0 = $t6
	syscall			# Print integer
	
	li $v0, 4		# Service code 4 to print an integer
	la $a0, newLine		# $a0 = newLine
	syscall			# Print newline
	
	j while	

exit:
	li $v0, 10		# Service code 10 to exit program
	syscall			# Exit	
