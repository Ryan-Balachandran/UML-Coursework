		.data
number1:	.float 3.14
number2:	.float 2.71

number3:	.double 3.14
number4:	.double 2.71

newLine:		.asciiz "\n"

		.text
# Use even number registers from co-processor 1
lwc1 $f2, number1		# $f2 = number1
lwc1 $f4, number2		# $f4 = number2
add.s $f12, $f2, $f4		# $f12 = $f2 + $f4

li $v0, 2			# Service code 2 to print a float
syscall				# Print float

ldc1 $f6, number3		# $f6 = number3
ldc1 $f8, number4		# $f8 = number4
add.d $f14, $f6, $f8		# $f14 = $f6 + $f8

li $v0, 4			# Service code 4 to print a string/character
la $a0, newLine			# $a0 = newLine
syscall				# Print newline

li $v0, 3			# Service code 3 to print a double
syscall				# Print double
