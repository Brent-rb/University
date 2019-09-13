####################################################################
# <naam van programma>
#
# Doel: If and else nabootsen
####################################################################
# Input: /
# Output: /
#
# Register gebruik:
# $t0: De waarde die we verglijken in de if statement
# $t1: een getal in op slagen
# $t2: een getal in op slagen
####################################################################
#
# if($t0 > 0) 
# 	$t1 = 10;
# else
# 	$t1 = 20;
# $t2 = 30;
####################################################################


	.data
#<Hier komen de gegevensdeclaraties>
	

###################### Code Segment ################################

	.text
	.globl main
main:
#<Hier komen de instructies>
	li 	$t0, -5
	blez 	$t0, twenty
	li 		$t1, 10
	b 		end
twenty:
	li 		$t1, 20

end:	
	li 		$t2, 30
	li 		$v0, 10
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