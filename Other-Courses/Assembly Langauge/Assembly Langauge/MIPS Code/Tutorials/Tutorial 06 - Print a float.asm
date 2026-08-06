		.data
PI: 		.float 3.14159		# Variable PI has float 3.14159

		.text
# Display result
li $v0, 2		# Service code 2 to print a float
lwc1 $f12, PI		# $f12 = PI
syscall			# Print float
