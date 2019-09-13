####################################################################
# <naam van programma>
#
# Doel: Een while loop nabootsen in assembly
####################################################################
# Input: /
# Output: /
#
# Register gebruik:
# $t0 : de eindwaarde voor het eindigen van de loop 
# $t3 : de teller van de loop
####################################################################
#
# Pseudo-code beschrijving:
# while($t3 < $t0)
#	$t3++;
#
####################################################################


	.data
#<Hier komen de gegevensdeclaraties>
	

###################### Code Segment ################################

	.text
	.globl main
main:

	li 		$t3, 0
loop:	
	li 		$t0, 30
	beq		$t3, $t0, end
	addi 	$t3, $t3, 1
	b loop
end:
	li $v0, 10
	syscall













####################################################################
# <naam van de functie en parameters>
#
# Doel: <Algemene beschrijving van de functie>
####################################################################
#
####################################################################
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