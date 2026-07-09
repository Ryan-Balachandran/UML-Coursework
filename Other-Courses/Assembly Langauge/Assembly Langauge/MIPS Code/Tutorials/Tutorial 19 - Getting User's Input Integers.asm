		.data
prompt:		.asciiz "Enter your age: "
message:	.asciiz "\nYour age us: "

		.text
# Prompt the user to enter age
li $v0, 4			# Service code 4 to print a string
la $a0, prompt			# $a0 = prompt
syscall				# Print string

# Get the user's age
li $v0, 5			# Service code 5 to read an integer
syscall				# Get user input

# Store result in t0
move $t0, $v0			# $t0 = $v0

# Display message
li $v0, 4			# Service code 4 to print a string
la $a0, message			# $a0 = message
syscall				# Print string

# Print or show the age
li $v0, 1			# Service code 1 to print an integer
move $a0, $t0			# $a0 = $t0
syscall				# Print integer
