		.data
message:	.asciiz "Enter the value of PI: "
zeroAsFloat:	.float	0.0

		.text
lwc1 $f4, zeroAsFloat		# $f4 = zeroAsFloat

# Display Message
li $v0, 4			# Service code 4 to print a string
la $a0, message			# $a0 = message
syscall				# Print string

li $v0, 6			# Service code 6 to read a float
syscall				# Read User input

# Display value
li $v0, 2			# Service code 2 to print a float
add.s $f12, $f0, $f4		# $f12 = $f0 + $f4
syscall				# Print float
