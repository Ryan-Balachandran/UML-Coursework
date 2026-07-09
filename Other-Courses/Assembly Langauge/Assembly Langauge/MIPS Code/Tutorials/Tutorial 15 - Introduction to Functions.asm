		.data
message: 	.asciiz "Hi, everybody. \nMy name is Ryan. \n"

		.text
# Main function
main:
	# jump and link
	jal displayMessage	# Call function
	
	addi $s0, $0, 5		# $s0 = $0 + 5
	
	# Display result
	li $v0, 1		# Service code 1 to print an integer
	add $a0, $0, $s0	# $a0 = $0 + $s0
	syscall			# Print 5

	# Tell the system that the program is done
	# Mandatory with functions
	li $v0, 10		# Service code 10 to exit program
	syscall			# Exit 


# displayMessage prints the message to the screen
# Define function
displayMessage:			# Function label
	li $v0, 4		# Service code 4 to print a string
	la $a0, message		# $a0 = message
	syscall			# Print message
	
	jr $ra			# Go back to call
