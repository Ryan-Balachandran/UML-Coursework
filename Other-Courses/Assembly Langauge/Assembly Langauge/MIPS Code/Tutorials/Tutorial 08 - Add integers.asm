		.data
number1:	.word 5		# Variable number1 has integer 5
number2:	.word 10	# Variable number2 has integer 10

		.text
# $zero or $0
lw $t0, number1($0)		# $t0 = number1
lw $t1, number2($0)		# $t1 = number2

add $t2, $t0, $t1		# $t2 = $t0 + $t1

# Display result
li $v0, 1			# Service code 1 to print an integer
add $a0, $0, $t2		# $a0 = $0 + $t2
syscall				# Print integer
