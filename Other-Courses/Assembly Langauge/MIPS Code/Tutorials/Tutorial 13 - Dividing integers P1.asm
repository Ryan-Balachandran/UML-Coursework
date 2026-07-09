		.data
#Not using RAM

		.text
addi $t0, $0, 30		# $t0 = $0 + 30
addi $t1, $0, 5			# $t1 = $0 + 5
	
# div takes 3 registers	
div $s0, $t0, $t1		# $s0 = 30 / 5

# Display result
li $v0, 1			# Service code 1 to print an integer
add $a0, $0, $s0		# $a0 = $0 + $s0
syscall				# Print integer
