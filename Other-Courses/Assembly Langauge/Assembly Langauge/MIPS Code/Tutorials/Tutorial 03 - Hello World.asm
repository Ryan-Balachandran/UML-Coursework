		.data
myMessage: 	.asciiz "Hello World \n"	# Variable myMessage has string "Hello World"

		.text
# Display result
li $v0, 4		# Service code 4 to print a string
la $a0, myMessage	# $a0 = myMessage
syscall			# Print string
