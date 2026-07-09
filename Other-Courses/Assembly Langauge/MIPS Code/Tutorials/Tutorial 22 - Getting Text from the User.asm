		.data
message:	.asciiz "Hello, "
userInput:	.space 20

		.text
main:
	# Getting User's input as text
	li $v0, 8			# Service code 8 to read text
	la $a0, userInput		# $a0 = userInput
	li $a1, 20			# $a1 = 20, Allocate 20 bytes for text
	syscall				# Read User input
	
	# Display hello
	li $v0, 4			# Service code 4 to print a string
	la $a0, message			# $a0 = message
	syscall				# Print message
	
	# Displays the name
	li $v0, 4			# Service code 4 to print a string
	la $a0, userInput		# $a0 = userInput
	syscall				# Print user's name

# Tell the system that this is the end of main
li $v0, 10		# Service code 10 to exit program
syscall			# Exit 
