		.data
myArray:	.space 12	# allocate 12 bytes or 3 integers (4 bytes each)

		.text

addi $s0, $0, 4			# $s0 = $0 + 4
addi $s1, $0, 10		# $s1 = $0 + 10
addi $s2, $0, 12		# $s2 = $0 + 12
	
# index = $t0
addi $t0, $0, 0			# $t0 = $0
	
# index 1
sw $s0, myArray($t0)		# $t0 = $s0 (4)
addi $t0, $t0, 4		# increment index by 1 (4 bytes)
	
# index 2
sw $s1 myArray($t0)		# $t0 = $s1 (10)
addi $t0, $t0, 4		# increment index by 1 (4 bytes)
	
# index 3
sw $s2, myArray($t0)		# $t0 = $s2 (12)
	
lw $t6, myArray($0)		# $t6 = myArray(first index)
	
li $v0, 1			# Service code 1 to print an integer
addi $a0, $t6, 0		# $a0 = $t6 + 0
syscall				# Print integer
