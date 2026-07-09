		.data
#Not using RAM

		.text
addi $t0, $0, 2000		# $t0 = $0 + 2000
addi $t1, $0, 10		# $t1 = $0 + 10

mult $t0, $t1			# $t0 * $t1
mflo $s0			# $s0 = lo

# Display result
li $v0, 1			# Service code 1 to print an integer
add $a0, $0, $s0		# $a0 = $0 + $s0
syscall				# Print integer
