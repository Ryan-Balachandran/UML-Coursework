		.data
# Not using RAM

		.text
# $zero or $0
addi $s0, $0, 10		# $s0 = $0 + 10
addi $s1, $0, 4			# $s1 = $0 + 4

# Mul uses three registers
mul $t0, $s0, $s1		# $t0 = $s0 * $s1

# Display result
li $v0, 1			# Service code 1 to print an integer
add $a0, $0, $t0		# $a0 = $0 + $t0
syscall				# Print integer
