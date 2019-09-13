####################################################################
	.data
#<Hier komen de gegevensdeclaraties>
printInfo:
	.asciiz "\n[1] Nieuwe Rij Toevoegen.\n[2] Rijen Uitprinten\n[3] Leeftijd Zoeken\n[0] Programma stoppen.\n" 

outOfBounds:
	.asciiz "Het ingegeven nummer is out of bounds.\n"

newline:
	.asciiz "\n"

geenRijen:
	.asciiz "Er zijn nog geen rijen toegevoegd.\n"

leeftijd:
	.asciiz "\tLeeftijd: "

naam:
	.asciiz "Naam: "

stad: 
	.asciiz "\tStad: "

geefNaam:
	.asciiz "Geef de naam in van de nieuwe nieuwe persoon: "

geefLeeftijd:
	.asciiz "Geef de leeftijd van deze persoon: "

geefStad:
	.asciiz "Geef de stad van deze persoon: "

geefGezochteLeeftijd:
	.asciiz "Geef de gezochte leeftijd in: "

endOfList:
	.asciiz "Einde van de lijst bereikt.\n"


###################### Code Segment ################################

	.text
	.globl main
main:
	li 	$s0, 0
askInfo:
	la	$a0, printInfo
	li 	$v0, 4
	syscall
	li 	$v0, 5
	syscall
	
	li 	$s7, 1
	beqz 	$v0, main_end
	beq 	$v0, 1, addRow
	beq 	$v0, 2, printRows
	beq 	$v0, 3, searchAge
	b 	askInfo
main_end:
	li 	$v0, 10
	syscall
	




#############################################################
		      #Subroutines#
#############################################################

addRow:
	li	$a0, 68
	li 	$v0, 9
	syscall
	move 	$t8, $v0
	move 	$t7, $v0

	la 	$a0, geefNaam
	li 	$v0, 4
	syscall

	li 	$v0, 8
	la 	$a0, ($t8)
	li 	$a1, 32
	syscall

	addi 	$t8, $t8, 32

	la 	$a0, geefLeeftijd
	li 	$v0, 4
	syscall

	li 	$v0, 5
	syscall
	sw 	$v0, ($t8)

	addi 	$t8, $t8, 4

	la 	$a0, geefStad
	li 	$v0, 4
	syscall

	li 	$v0, 8
	la 	$a0, ($t8)
	la 	$a1, 28
	syscall

	addi 	$t8, $t8, 28
	li 	$t6, 0
	sw 	$t6, ($t8)



	

	move 	$t0, $s0
	beqz 	$t0, addRow_connect_first

addRow_loop:
	addi 	$t0, $t0, 64
	lw 	$t1, ($t0)
	beqz  	$t1, addRow_connect
	move 	$t0, $t1
	b 	addRow_loop
addRow_connect:
	sw 	$t7, ($t0)
	b 	askInfo

addRow_connect_first:
	move 	$s0, $t7
	b 	askInfo	

	
	

	
printRows:
	move 	$t0, $s0
	beqz 	$t0, printRows_noRows
printRows_loop:		
	jal 	printOneRow

	lw 	$t0, ($t0)

	beqz 	$t0, askInfo
	b 	printRows_loop

	
printRows_noRows:
	la 	$a0, geenRijen
	li 	$v0, 4
	syscall
	b 	askInfo





searchAge:
	la 	$a0, geefGezochteLeeftijd
	li 	$v0, 4
	syscall

	li 	$v0, 5
	syscall

	addi 	$t1, $v0, 0

	move 	$t0, $s0
	beqz 	$t0, printRows_noRows
searchAge_loop:
	addi 	$t0, $t0, 32

	lw 	$t2, ($t0)

	beq 	$t2, $t1, searchAge_match

	addi 	$t0, $t0, 32

	lw 	$t0, ($t0)
	beqz 	$t0, searchAge_endOfList
	b 	searchAge_loop


searchAge_match:
	subi 	$t0, $t0, 32
	jal 	printOneRow
	lw 	$t0, ($t0)
	beqz 	$t0, searchAge_endOfList
	b 	searchAge_loop

searchAge_endOfList:
	la 	$a0, endOfList
	li 	$v0, 4
	syscall
	b 	askInfo




printOneRow:
	la 	$a0, naam
	li 	$v0, 4
	syscall
	
	la 	$a0, ($t0)	
	syscall

	la 	$a0, leeftijd
	syscall

	addi 	$t0, $t0, 32

	lw	$a0, ($t0)
	li 	$v0, 1
	syscall

	la 	$a0, newline
	li 	$v0, 4
	syscall

	la 	$a0, stad
	syscall

	addi 	$t0, $t0, 4
	
	la	$a0, ($t0)
	li 	$v0, 4
	syscall

	addi 	$t0, $t0, 28

	jr 	$ra

	
	


















