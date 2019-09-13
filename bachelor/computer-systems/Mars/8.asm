####################################################################
	.data
#<Hier komen de gegevensdeclaraties>
printInfo:
	.asciiz "\n[1] Nieuwe Rij Toevoegen.\n[2] Rij Uitprinten\n[3] Rij Wijzigen\n[0] Programma stoppen.\n" 

geheugenVol:
	.asciiz "Het geheugen is vol\n"

veranderRij:
	.asciiz "Geef het rij nummer dat je wil uitprinten: "

outOfBounds:
	.asciiz "Het ingegeven nummer is out of bounds"

newline:
	.asciiz "\n"

leeftijd:
	.asciiz "Leeftijd: "

naam:
	.asciiz "Naam: "

stad: 
	.asciiz "Stad: "

geefNaam:
	.asciiz "Geef de naam in van de nieuwe nieuwe persoon: "

geefLeeftijd:
	.asciiz "Geef de naam in van de leeftijd van deze persoon: "

geefStad:
	.asciiz "Geef de naam van de stad van deze persoon: "

geefRij:
	.asciiz "Geef de rij nummer in die je wilt uitprinten: "

.align 2
array:
	.space 320


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
	beq 	$v0, 2, printRow
	beq 	$v0, 3, changeRow
	b 	askInfo
main_end:
	li 	$v0, 10
	syscall
	




#############################################################
		      #Subroutines#
#############################################################

addRow:
	beq 	$s0, 5, addRow_error
	la 	$t0, array
	mul 	$t7, $s0, 64
	add 	$t0, $t0, $t7

addRow_new:
	la 	$a0, geefNaam
	li 	$v0, 4
	syscall
	la 	$a0, ($t0)
	li 	$a1, 32
	li 	$v0, 8
	syscall
	
	la 	$a0, geefLeeftijd
	li 	$v0, 4
	syscall

	addi 	$t0, $t0, 32

	li 	$v0, 5
	syscall
	sw	$v0, ($t0)

	addi 	$t0, $t0, 4
	
	la 	$a0, geefStad
	li 	$v0, 4
	syscall

	la 	$a0, ($t0)
	li 	$a1, 28
	li 	$v0, 8
	syscall

	beqz 	$s7, addRow_end

	addi 	$s0, $s0, 1
addRow_end:
	b 	askInfo
addRow_error:
	la 	$a0, geheugenVol
	li 	$v0, 4
	syscall
	b 	addRow_error



	
printRow:
	la 	$t0, array
	li 	$v0, 4
	la 	$a0, geefRij
	syscall

	li 	$v0, 5
	syscall
	
	blt 	$v0, 0, printRow_outOfBounds
	bge 	$v0, $s0, printRow_outOfBounds

	mul 	$t8, $v0, 64
	add 	$t0, $t0, $t8

	la 	$a0, naam
	li 	$v0, 4
	syscall
	la 	$a0, ($t0)
	syscall

	la 	$a0, leeftijd
	syscall
	addi 	$t0, $t0, 32
	lw 	$a0, ($t0)
	li 	$v0, 1
	syscall
	la 	$a0, newline
	li 	$v0, 4
	syscall
	la 	$a0, stad
	syscall
	addi 	$t0, $t0, 4
	la 	$a0, ($t0)
	syscall

	b 	askInfo

printRow_outOfBounds:
	la 	$a0, outOfBounds
	li 	$v0, 4
	syscall
	b 	askInfo






changeRow:
	la 	$a0, veranderRij
	li 	$v0, 4
	syscall
	li 	$v0, 5
	syscall

	bge 	$v0, $s0, printRow_outOfBounds

	la 	$t0, array
	mul 	$t8, $v0, 64
	add 	$t0, $t8, $t0
	li 	$s7, 0
	b 	addRow_new
	

	





















