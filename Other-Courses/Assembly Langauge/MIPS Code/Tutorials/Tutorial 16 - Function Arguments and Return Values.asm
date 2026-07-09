		.data

		.text
# Main function
main:
	addi $a1, $0, 50		# $a1 = $0 + 50
	addi $a2, $0, 100		# $a2 = $0 + 100

	jal addNumbers			# Call function
	
	# Display result
	li $v0, 1			# Service code 1 to print an integer
	addi $a0, $v1, 0		# $a0 = $v1 + 0
	syscall				# Print 150

	# Tell the system that the program is done
	li $v0, 10			# Service code 10 to exit program
	syscall				# Exit 

# displayMessage prints the message to the screen
addNumbers:
	add $v1, $a1, $a2		# $v1 = $a1 + $a2
	jr $ra				# Go back to call
