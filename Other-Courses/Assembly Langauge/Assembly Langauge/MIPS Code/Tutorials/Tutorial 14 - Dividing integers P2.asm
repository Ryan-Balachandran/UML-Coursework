		.data
#Not using RAM

		.text
addi $t0, $0, 30		# $t0 = $0 + 30
addi $t1, $0, 5			# $t1 = $0 + 5

# div takes 2 registers and a +constant/- constant
div $s0, $t0, 10		# $s0 = 30 / 10

# Display result
li $v0, 1			# Service code 1 to print an integer
add $a0, $0, $s0		# $a0 = $0 + $s0
syscall				# Print integer

#---------------------------------------------------

addi $t2, $0, 30		# $t2 = $0 + 30
addi $t3, $0, 6			# $t3 = $0 + 6

# div takes 2 registers, stores in low or high
div $t0, $t1			# 30 / 6

mflo $s0			# $s0 = lo (Quotient)
mfhi $s1			# $s1 = hi (Remainder)

# Display result
li $v0, 1			# Service code 1 to print an integer
add $a0, $0, $s0		# $a0 = $0 + $s0 for quotient
# add $a0, $0, $s1		# $a0 = $0 + $s1 for remainder
syscall				# Print integer
