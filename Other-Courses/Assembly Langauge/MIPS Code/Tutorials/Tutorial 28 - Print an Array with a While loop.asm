		.data
myArray:	.space 12	# allocate 12 bytes or 3 integers (4 bytes each)
newLine:	.asciiz "\n"
		.text

main:	
	addi $s0, $0, 4		# $s0 = $0 + 4
	addi $s1, $0, 10	# $s1 = $0 + 10
	addi $s2, $0, 12	# $s2 = $0 + 12
	
	# index = $t0
	addi $t0, $0, 0		# $t0 = $0
	
	# index 1
	sw $s0, myArray($t0)	# $t0 = $s0 (4)
	addi $t0, $t0, 4	# increment index by 1
	
	# index 2
	sw $s1 myArray($t0)	# $t0 = $s1 (10)
	addi $t0, $t0, 4	# increment index by 1
	
	# index 3
	sw $s2, myArray($t0)	# $t0 = $s2 (12)
	
	# clear $t0 to 0
	addi $t0, $0, 0		# $t0 = $0 + 0

while:
	beq $t0, 12, exit	# Branch if at end of array - goto exit
	lw $t6, myArray($t0)	# load array element into $t6
	
	addi $t0, $t0, 4	# increment index by 1 (4 bytes)
	
	# Print current number
	li $v0, 1		# Service code 1 to print an integer
	move $a0, $t6		# $a0 = $t6
	syscall			# Print integer
	
	li $v0, 4		# Service code 1 to print an integer
	la $a0, newLine		# $a0 = newLine
	syscall			# Print newline
	
	j while	

exit:
	li $v0, 10		# Service code 10 to exit program
	syscall			# Exit	
