
newline:
	jal 	getline			# retrieve input

	li      $t5, 0			# $t5 = index to inBuf
	li      $a3, 0			# $a3 = index to TabToken
	
	la 	$s1, Q0			# CUR = Q0
	
	# la	$t7, LOC		# $t7 = beginning address of program

nextState:
	lw	$s2, 0($s1)		# ACT = STAB[CUR][0]
	
	jalr	$v1, $s2		# Save return addr in $v1

	sll	$s0, $s0, 2		# compute byte offset of T
	add	$s1, $s1, $s0		# locate the next state
	la      $s1, ($s1)
	lw	$s1, ($s1)		# CUR = STAB[CUR][T], next State in $s1
	sra	$s0, $s0, 2		# reset $s0 for T

	b	nextState
	
# IMPLEMENT-----------------------------------------------------------------------------------------
# nextLine:
	# Read an input string and sve token and type in tabToken
	# If(tabToken[0][0] == '#') goto exit
	
	# i = 0;	//index to TOKENS[][]
	
# nextTok:
	# if(tabToken[i+1][0] != ':') goto operator
	# TOKEN = tabToken[i][0]
	# valVar = VAR (TOKEN, 1)	// store label in symTab
	# i += 2	// skip ':'
	
# operator: 
	# i++		// do nothing with operator
	# isComma = true
	
# checkVar:
	# if(tabToken[i][0] == '#') goto dump
	# if(!isComma || tabToken[i][1] != 2) goto nextVar
	
# nextVar: 
	# isComma = (tabToken[i][0] == ',')
	# i++
	# goto checkVar
# IMPLEMENT-----------------------------------------------------------------------------------------
	
dump:
	jal     printline		# echo print input string
	jal	printTabTok		# output TabToken
	
	jal	clearInBuf		# clear input buffer
	jal	clearTabTok		# clear TabToken
	#jal 	print symTab		# IMPLEMENT-----------------------------------------------------------------------------------------
	
	la 	$a0, newLine		# Prompt to enter a new line
	li 	$v0, 4			# Service code 4 to print a string
	syscall				# Print newLine
	
	b 	newline			# read another string 

exit:	
	li	$v0, 10
	syscall

##################################
# ACT1:
# 	- $t5: Get next char
#	- T = char type
##################################
ACT1: 
	lb	$a0, inBuf($t5)			# $a0: next char
        jal     lin_search			# $s0: T (char type)
        addi    $t5, $t5, 1			# $t5++
        jr      $v1

##################################################################
# lin_search:
#	- Linear search of Tabchar
#
#	- $a0: char key
#	- $s0: char type, T
#################################################################
lin_search:
        li      $t0, 0				# index to Tabchar
        li      $s0, 7				# return value, type T
        
loopSearch:
        beq     $t1, 0x5c, fail			# branch to done if no match is found in Tabchar
        lb      $t1, Tabchar($t0)		# Load byte from Tabchar

        beq     $t1, $a0, match			# branch if $t1 = $a0, goto match
        addi    $t0, $t0, 8			# skip character and character type to get to next character
        
        b       loopSearch
        
match:
        lw      $s0, Tabchar+4($t0)		# return char type
        
fail:
        jr      $ra
        
###############################################
# ACT2:
#	- save char to TOKEN for the first time
#	- save char type as Token type
#	- set remaining token space
###############################################
ACT2:
	li      $s3, 0				# initialize index to TOKEN char 
	sb      $a0, TOKEN($s3)			# save 1st char to TOKEN
	addi    $t0, $s0, 0x30			# T type in ASCII
	sb      $t0, TOKEN+10($s3)		# save T as Token type
	li      $t0, '\n'			
	sb      $t0, TOKEN+11($s3)		# NULL to terminate an entry
	addi    $s3, $s3, 1
	jr      $v1
	
#############################################
# ACT3:
#	- collect char to TOKEN
#	- update remaining token space
#############################################
ACT3:
	bgt     $s3, 7, lenError		# TOKEN length error
	sb      $a0, TOKEN($s3)			# save char to TOKEN
	addi    $s3, $s3, 1			# $s3: index to TOKEN
	jr      $v1     
	
lenError:
	li      $s0, 7				# T = 7 for token length error
	jr      $v1
	
#############################################
#  ACT4:
#	- move TOKEN to TabToken
############################################
ACT4:
	lw      $t0, TOKEN($0)			# get 1st word of TOKEN
	sw      $t0, TabToken($a3)		# save 1st word to TabToken
	lw      $t0, TOKEN+4($0)		# get 2nd word of TOKEN
	sw      $t0, TabToken+4($a3)		# save 2nd word to TabToken
	lw      $t0, TOKEN+8($0)		# get Token Type
	sw      $t0, TabToken+8($a3)		# save Token Type to TabToken
	addi    $a3, $a3, 12			# update index to TabToken
        
	jal     clearTok			# clear 3-word TOKEN
	jr      $v1

##################################
# VAR()
# 	- IMPLEMENT--------------------------------------------------------------------------------
##################################

# VAR (TOKEN, DEFN)
# {
#	symIndex = searchSymTab(TOKEN))		// -1 if not found; index if found
#	if (symIndex < 0)			// first occurence
#	{	
#		newStatus = 0x4 | DEFN
#		symIndex = saveSymTab(TOKEN, newStatus);
#	}
#	else
#	{
#		oldStatus = symTab[symIndex][2];
#		// determine the new status (F flag = 0)
#		newStatus = oldStatus & 0x2 | ((oldStatus & 0x1) << 1);		// set A flag
#		newStatis = newStatus | DEFN		// set D flag
#		symTab[symIndex][2] = newStatus;
#	}
#	retVal = symACTS(newStatus, symIndex);		// from the jump table
#	retVar: return retVal
# }
# IMPLEMENT-----------------------------------------------------------------------------------------

VAR:
	jr	$ra


	


