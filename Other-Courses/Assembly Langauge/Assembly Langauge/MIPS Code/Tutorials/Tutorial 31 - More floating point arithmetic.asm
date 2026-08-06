		.data

number1:	.float 3.00	# 15.00 for divide
number2:	.float 2.00	# 3.00 for divide

newLine:	.asciiz "\n"

		.text
# Use even number registers from co-processor 1
lwc1 $f2, number1		# $f2 = number1
lwc1 $f4, number2		# $f4 = number2
mul.d $f12, $f2, $f4		# $f12 = $f2 * $f4
# div.d $f12, $f2, $f4		# $f12 = $f2 / $f4
# sub.d $f12, $f2, $f4		# $f12 = $f2 - $f4

li $v0, 3			# Service code 3 to print a double
syscall				# Print newline and double
