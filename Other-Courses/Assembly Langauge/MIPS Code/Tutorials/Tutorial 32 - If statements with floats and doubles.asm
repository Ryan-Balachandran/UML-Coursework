		.data
message1:	.asciiz "It was true.\n"
message2:	.asciiz "It was false.\n"

num1:		.float 10.4
num2:		.float 10.6

		.text
main:
	lwc1 $f0, num1		# $f0 = num1
	lwc1 $f2, num2		# $f2 = num2
	
	c.eq.s $f0, $f2		# is $f0 == $f2?
	# c.le.s $f0, $f2
	
	bc1t exit
	# or bc1f
	
	li $v0, 4		# Service code 4 to print a string
	la $a0, message2	# $a0 = message1
	syscall			# Print message

li $v0, 10		# Service code 10 to exit program
syscall			# Exit	

exit:
	li $v0, 4		# Service code 4 to print a string
	la $a0, message1	# $a0 = message1
	syscall			# Print message