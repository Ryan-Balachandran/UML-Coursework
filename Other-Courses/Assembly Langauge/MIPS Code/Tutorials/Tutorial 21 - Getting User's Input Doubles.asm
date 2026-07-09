		.data
prompt:		.asciiz "Enter the value of e: "

		.text
# Display Message
li $v0, 4			# Service code 4 to print a string
la $a0, prompt			# $a0 = message
syscall 			# Print string

# Get the Double from the user
li $v0, 7			# Service code 7 to read a double
syscall				# Read User input

# Display the User's input
li $v0, 3			# Service code 3 to print a double
add.d $f12, $f0, $f10		# $f12 = $f0 + $f4
syscall
