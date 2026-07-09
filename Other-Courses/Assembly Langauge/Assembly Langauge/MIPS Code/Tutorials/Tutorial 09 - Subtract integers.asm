		.data
number1:	.word 20	# Variable number1 has integer 20
number2:	.word 8		# Variable number2 has integer 8

		.text
				# functions can't modify value in 's' registers
lw $s0, number1			# $s0 = number1
lw $s1, number2			# $s1 = number2

sub $t0, $s0, $s1		# $t0 = 20 - 8

# Display result
li $v0, 1			# Service code 1 to print an integer
move $a0, $t0			# $a0 = $t0
syscall				# Print integer
