####################################################################
	.data
#<Hier komen de gegevensdeclaraties>
ask:
	.asciiz "Geef een zin in: "

isPalin:
	.asciiz "De ingegeven zin is een palindroom.\n"

isNoPalin:
	.asciiz "De ingegeven zin is geen palindroom.\n"

sask_char:
	.asciiz "Geef het nieuwe karakter in: "

sask_place:
	.asciiz "Geef de positie in van het karakter dat je wil vervangen: "

newline:
	.asciiz "\n"


###################### Code Segment ################################

	.text
	.globl main
main:
	la 	$a0, ask
	li 	$v0, 4
	syscall

	li	$s0, 215		#Begin zin inleze
	sub 	$sp, $sp, $s0
	la	$s1, 0($sp)
	li 	$v0, 8
	la 	$a0, 0($s1)
	addi	$a1, $s0, 0
	syscall			#Eind zin inleze

	la 	$a0, ($s1)
	jal 	deleteEnter
	
	la 	$a0, ($s1)	#Begin get length
	jal 	getLength
	la 	$s2, ($v0)	#Eind get length

	#la 	$a0, ($s1)
	#la 	$a1, ($s2)
	#jal 	reverseString
	#la 	$a0, ($s1)
	#li 	$v0, 4
	#syscall

	#la 	$a0, ($s1)
	#la 	$a1, ($s2)
	#jal 	checkPalin
	#beq 	$v0, 1, loadIsPalin
	#beqz 	$v0, loadIsNoPalin
	#syscall

	la 	$a0, ($s1)
	la 	$a1, ($s2)
	jal 	printUneven
	
	la 	$a0, ($s1)
	li 	$v0, 4
	syscall
	

	li 	$v0, 10
	syscall

loadIsPalin:
	la 	$a0, isPalin
	li	$v0, 4
	jr 	$ra

loadIsNoPalin:
	la	$a0, isNoPalin
	li 	$v0, 4
	jr 	$ra





#############################################################
		      #Subroutines#
#############################################################

getLength:
	la	$t0, 0($a0)
	li 	$t1, 0
getLength_loop:
	lbu 	$t2, 0($t0)
	beqz 	$t2, getLength_end
	addi 	$t0, $t0, 1
	addi 	$t1, $t1, 1
	b 	getLength_loop

getLength_end:
	addi 	$v0, $t1, 0
	jr 	$ra




reverseString:
	la 	$t0, ($a0)
	add 	$t1, $t0, $a1
	subi 	$t1, $t1, 1
reverseString_loop:
	bge 	$t0, $t1, reverseString_end
	lbu 	$t2, ($t0)
	lbu 	$t3, ($t1)
	sb 	$t2, ($t1)
	sb 	$t3, ($t0)
	addi 	$t0, $t0, 1
	subi 	$t1, $t1, 1
	b 	reverseString_loop

reverseString_end:
	jr 	$ra
	
	


checkPalin:
	la 	$t0, ($a0)
	add 	$t1, $t0, $a1
	subi 	$t1, $t1, 1
checkPalin_loop:
	bge	$t0, $t1, checkPalin_isPalin
	lbu 	$t2, ($t0)
	lbu 	$t3, ($t1)
	bne 	$t2, $t3, checkPalin_isNoPalin
	addi 	$t0, $t0, 1
	subi 	$t1, $t1, 1
	b 	checkPalin_loop

checkPalin_isPalin:
	li 	$v0, 1
	jr 	$ra
checkPalin_isNoPalin:
	li 	$v0, 0
	jr 	$ra
	



deleteEnter:
	la 	$t0, ($a0)
deleteEnter_loop:
	lbu	$t1, ($t0)
	beq 	$t1, 10, deleteEnter_LFend
	beq 	$t1, $zero, deleteEnter_end
	addi 	$t0, $t0, 1
	b 	deleteEnter_loop
deleteEnter_LFend:
	sb 	$zero, ($t0)
deleteEnter_end:
	jr 	$ra



changeChar:
	la 	$t0, ($a0)
changeChar_ask:
	la 	$a0, sask_place
	li 	$v0, 4
	syscall

	li 	$v0, 5
	syscall
	bge 	$v0, $a1, changeChar_ask
	add 	$t0, $t0, $v0

	la 	$a0, sask_char
	li 	$v0, 4
	syscall

	li 	$v0, 12
	syscall
	la 	$t1, ($v0)

	la 	$a0, newline
	li 	$v0, 4
	syscall

	sb 	$t1, ($t0)
	jr 	$ra
		





printUneven:
	la 	$t0, ($a0)
	li 	$t8, 2
	la 	$a0, newline
	li 	$v0, 4
	syscall
	li 	$v0, 11
printUneven_loop:
	lbu 	$t1, ($t0)
	beqz 	$t1, printUneven_end

	div 	$t1, $t8
	mfhi 	$t2
	bnez 	$t2, printUneven_printChar
printUneven_increment:
	addi 	$t0, $t0, 1
	b 	printUneven_loop

printUneven_printChar:
	lbu 	$a0, ($t0)
	syscall
	b 	printUneven_increment

printUneven_end:
	la 	$a0, newline
	li 	$v0, 4
	syscall
	jr 	$ra

