		.data
newLine:		.asciiz "\n"	# Prints a new line
		.text
# Main function
# functions can modify values in 't' register, but not 's' registers
# 's' registers are caller saved
# 't' registers are callee saved
main:
	addi $s0, $0, 10		# $s0 = $0 + 10
	
	jal increaseMyRegister		# Call function
	
	# Diplay result
	li $v0, 4			# Service code 4 to print a string
	la $a0, newLine			# $a0 = newLine
	syscall				# Print new line
	
	jal printTheValue		# Call function

	# Tell the system that the program is done
	li $v0, 10			# Service code 10 to exit program
	syscall				# Exit 

increaseMyRegister:
	# when using 's' register, must save it to the stack
	# want old variable to be available in main
	addi $sp, $sp, -8		# store 8 bytes in the stack - subtract to allocate
	sw $s0, 0($sp)			# Save old value on the stack
	sw $ra, 4($sp)			# Save return address of function to stack
	
	addi $s0, $s0, 30		# $s0 = 10 + 30
	
	# Nested function
	jal printTheValue		# Call function
	
	lw $s0, 0($sp)			# Restore word from stack to register $s0
	lw $ra, 4($sp)			# Restore function from stack to return address
	addi $sp, $sp, 8		# Restore stack
	
	jr $ra				# Go back to call
	
printTheValue:
	# Display result
	li $v0, 1			# Service code 1 to print an integer
	move $a0, $s0			# $a0 = $s0
	syscall				# Print integer

	jr $ra				# Go back to call
