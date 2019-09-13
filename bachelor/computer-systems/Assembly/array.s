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
	.word 5,6,7,8,9,0
newline:
	.asciiz "\n"
aantal:
	.asciiz "\n Het aantal elementen in de array is: "
aantaloneven:
	.asciiz "\n Het aantal oneven getallen in de array is: "


###################### Code Segment ################################

	.text
	.globl main
main:
#<Hier komen de instructies>
	li	$t0, 0 	#Teller op nul zetten
	li 	$s0, 4 	#4 in s0 stoppen
	li 	$v0, 1
	li 	$t3, 0	#oneven teller
	li 	$s1, 2
loop:
	mul	$t1, $t0, $s0 	#De teller vermenigvuldigen met 4
	lw	$t2, array($t1)	#Het $t1'de element uit de array halen
	beqz	$t2, end		#Als het getal 0 is --> stoppen
	move	$a0, $t2		#de waarde van $t2 in $a0 stoppen
	syscall			#$a0 afdrukken
	addi	$t0, $t0, 1	#Teller verhogen
	rem	$t4, $t2, $s1
	bnez	$t4, adduneven
	b 	loop		#loop terug beginnen
adduneven:
	addi $t3, $t3, 1
	b 	loop
end:
	li 	$v0, 4		#4 in v0 laden --> strings afprinten
	la 	$a0, newline	#Newline in a0 laden
	syscall			#Newline printen
	la 	$a0, aantal	#De string aantal in $a0 laden
	syscall			#de string aantal afprinten
	li	$v0, 1		#1 in v0 laden --> cijfers afprinten
	move	$a0, $t0		#Teller in a0 inladen
	syscall			#Teller afprinten
	li 	$v0, 4		#4 in v0 laden --> strings afprinten
	la	$a0, newline	#newline in a0 inladen
	syscall			#newline afprinten
	li 	$v0, 10		#Einde
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
