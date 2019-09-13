####################################################################
	.data
#<Hier komen de gegevensdeclaraties>

ask:
	.asciiz "Geef het fibonnaci getal dat je wilt: "


###################### Code Segment ################################

	.text
	.globl main
main:
	li 	$v0, 4
	la 	$a0, ask
	syscall
	li 	$v0, 5
	syscall
	move 	$a0, $v0
	jal 	fibonnaci
	move 	$a0, $v0
	li 	$v0, 1
	syscall
main_end:
	li 	$v0, 10
	syscall




#############################################################
		      #Subroutines#
#############################################################

	
	
	
fibonnaci:
	beq 	$a0, 1, returnOne
	beq 	$a0, 2, returnOne

	subi 	$sp, $sp, 4
	sw 	$ra, ($sp)

	subi 	$a0, $a0, 1
	subi 	$sp, $sp, 4
	sw 	$a0, ($sp)
	jal 	fibonnaci
	lw 	$a0, ($sp)
	addi 	$sp, $sp, 4
	subi 	$a0, $a0, 1

	subi 	$sp, $sp, 4
	sw 	$v0, ($sp)
	jal 	fibonnaci
	
	lw 	$t0, ($sp)
	addi 	$sp, $sp, 4
	move 	$t1, $v0
	add 	$t0, $t0, $t1

	lw 	$ra, ($sp)
	addi 	$sp, $sp, 4

	move 	$v0, $t0
	jr 	$ra

returnOne:
	li 	$v0, 1
	jr 	$ra









