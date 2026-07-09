		.data
A:		.space 12		# Array A has space for 3 integers
prompt:		.asciiz "Please enter an integer: "
length:		.word 3			# Length of array A is 3

		.text
main:
	# Index of array = $t0
	addi 	$t0, $zero, 0		# Initialize first index of array A to 0
	
	# Get first integer from user
	li 	$v0, 4			# Service code 4 to print a string
	la 	$a0, prompt		# Load string into register a0
	syscall				# Print string
	
	li 	$v0, 5			# Service code 5 to read an integer
	syscall				# Get user input
	
	move 	$s0, $v0		# Move input to register $s0
	sw 	$s0, A($t0)		# Save input from register $s0 into first index of array A
	addi 	$t0, $t0, 4		# increment index of Array A by 4
	
	# Get second integer from user
	li 	$v0, 4			# Service code 4 to print a string
	la 	$a0, prompt		# Load string into register a0
	syscall				# Print string
	
	li 	$v0, 5			# Service code 5 to read an integer
	syscall				# Get user input
	
	move 	$s0, $v0		# Move input to register $s0
	sw 	$s0, A($t0)		# Save input from register $s0 into second index of array A
	addi 	$t0, $t0, 4		# increment index of array A by 4
	
	# Get third integer from user
	li 	$v0, 4			# Service code 4 to print a string
	la 	$a0, prompt		# Load string into register a0
	syscall				# Print string
	
	li 	$v0, 5			# Service code 5 to read an integer
	syscall				# Get user input
	
	move 	$s0, $v0		# Move input to register $s0
	sw 	$s0, A($t0)		# Save input from register $s0 into third index of array A
	
	la 	$a1, A			# Base address of array A
	lw 	$a2, length		# length of array
	
	jal 	average			# Call function
	
	# Display result
	li 	$v0, 1			# Service code 1 to print an integer
	move 	$a0, $v1		# move the value in register $v1 to register $a0
	syscall
	
# Tell the system that the program is done
li $v0, 10		# Service code 10 to exit program
syscall			# Exit 
	
# Average function takes 3 numbers, adds them, and divides by three then returns the result
# Argument 1 is the address of the array A stored in register $a1
# Argument 2 is the number of integers contained in the array A stored in register $a2
# The return value is passed to return register $v1
average:
	lw 	$t1, 0($a1)		# Take the first element of array A stored in register and $a1 and load it into register $t1
	addi $	t2, $t1, 0		# Add the first element of array A to register $t2
	
	lw 	$t1, 4($a1)		# Take the second element of array A stored in register $a1 and load it into register $t1
	add 	$t2, $t2, $t1		# Add the second element of array A to the first element stored in register $t2 
	
	lw 	$t1, 8($a1)		# Take the third element of array A stored in register $a1 and load it into register $t1
	add 	$t2, $t2, $t1		# Add the third element of array A to the sum of the first and second element stored in register $t2
	
	div 	$t2, $a2		# Divide the value of register $t2 by the length of array A stored in register $a2
	mflo 	$v1			# Move the result of the division from lo register to register $v1

	jr 	$ra			# Go back to call
