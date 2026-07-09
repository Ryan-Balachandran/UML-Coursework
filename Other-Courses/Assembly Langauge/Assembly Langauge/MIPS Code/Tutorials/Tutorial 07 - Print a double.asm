		.data
myDouble:	.double 7.202		# Variable myDouble has double 7.202
zeroDouble:	.double 0.0		# Variable zeroDouble has double 0.0

		.text
# Doubles dont have $zero, need to make your own
ldc1 $f2, myDouble		# $f2 = myDouble  (takes up f2 and f3)
ldc1 $f0, zeroDouble		# $f0 = zeroDouble  (takes up f0 and f1)

# Display result
li $v0, 3			# Service code 3 to print a double
add.d $f12, $f2, $f0		# $f12 = $f2 + $f0
syscall				# Print double
