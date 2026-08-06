		.data
#Not using RAM

		.text
addi $s0, $0, 4			# $s0 = $0 + 4

sll $t0, $s0, 2			# $t0 = $s0 * 2

# Display result
li $v0, 1			# Service code 1 to print an integer
add $a0, $0, $t0		# $a0 = $0 + $t0
syscall				# Print integer
