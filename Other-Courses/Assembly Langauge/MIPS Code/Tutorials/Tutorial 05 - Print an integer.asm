		.data
age: 		.word 23	# Variable age has integer 23

		.text
# Display result
li $v0, 1		# Service code 1 to print an integer
lw $a0, age		# $a0 = age
syscall			# Print word
