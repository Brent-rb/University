####################################################################
# <naam van programma>
#
# Doel: <Algemene beschrijving van het programma>
####################################################################
# Input: <welke invoer wordt er gebruikt>
# Output: <welke uitvoer wordt er geproduceerd>
#
# Register gebruik:
# <uitleg over het gebruik van de registers, bijv. welk registers 
# worden gebruikt om de diverse gegevens in te bewaren>
####################################################################
#
# Pseudo-code beschrijving:
# < speudo-code die de logische structuur duidelijk maakt>
#
####################################################################


	.data
#<Hier komen de gegevensdeclaraties>
array:
	.word 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
newline:
	.asciiz "\n"

###################### Code Segment ################################

	.text
	.globl main
main:
#<Hier komen de instructies>
	li	$t0, 2
	li 	$s0, 4
	li	$t2, 0
	li 	$t3, 1
	
loop:
	subi	$t7, $t0, 20
	beqz	$t7, end
	mul 	$t1, $t0, $s0
	mul 	$t4, $t2, $s0
	mul 	$t5, $t3, $s0
	lw	$s1, array($t4)
	lw 	$s2, array($t5)
	add	$t6, $s2, $s1
	sw	$t6, array($t1)
	lw	$a0, array($t1)
	li 	$v0, 1
	syscall
	la	$a0, newline
	li 	$v0, 4
	syscall
	addi	$t0, $t0, 1
	addi	$t2, $t2, 1
	addi 	$t3, $t3, 1
	b 	loop
end:
	li	$v0, 10
	syscall












####################################################################
# <naam van de functie en parameters>
#
# Doel: <Algemene beschrijving van de functie>
####################################################################
# Input: <welke invoer wordt er gebruikt>
# Output: <welke uitvoer wordt er geproduceerd>
#
# Register gebruik:
# <uitleg over het gebruik van de registers, bijv. welk registers 
# worden gebruikt om de diverse gegevens in te bewaren>
####################################################################
#
# Pseudo-code beschrijving:
# < speudo-code die de logische structuur duidelijk maakt>
#
####################################################################




####################################################################
# <naam van de functie en parameters>
#
# Doel: <Algemene beschrijving van de functie>
####################################################################
# Input: <welke invoer wordt er gebruikt>
# Output: <welke uitvoer wordt er geproduceerd>
#
# Register gebruik:
# <uitleg over het gebruik van de registers, bijv. welk registers 
# worden gebruikt om de diverse gegevens in te bewaren>
####################################################################
#
# Pseudo-code beschrijving:
# < speudo-code die de logische structuur duidelijk maakt>
#
####################################################################
