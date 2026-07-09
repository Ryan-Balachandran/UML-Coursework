		.data
myCharacter: 	.byte 'n'	# Variable myCharacter has character 'n'

		.text
# Display result
li $v0, 4		# Service code 4 to print a string/character
la $a0, myCharacter	# $a0 = myCharacter
syscall			# Print character
