####################################################################
# Voorbeeldprogramma 3
#
# Doel: 
# Inoefenen van subroutines. Zet de tekst op label "tekst" om naar hoofdletters, waar van toepassing. 
# ##################################################################
# Register gebruik
#
# Zelf te kiezen
####################################################################
#
# pseudo-code main:
# 
# positie = 0;
# teken = tekst[positie];
# while(teken != 0)
# {
#     teken = teken(toupper);
#     tekst[positie] = teken;
#     positie++;
#     teken = tekst[positie];
# }
# Print tekst;
###################### Data Segment ################################
	.data
tekst:
	.asciiz	"DiT iS eEn test!?"

###################### Code Segment ################################
	.text
	.globl main
main:
	la	$a0, tekst
	li 	$v0, 4
	li 	$t0, 0
	add	$t1, $a0, $zero
	addi	$t0, $t0, 1
	la 	$t2, tekst($t0)
	addi	tekst($t0), teskt($t0), 1
	
	la	$a0, ($t2)
	syscall

	li 	$v0, 10
	syscall 

####################################################################
# toupper
#
# Doel: Verander 1 karakter naar een hoofdletter, indien van toepassing
####################################################################
# Input: $a0: invoerkarakter
# Output: $v0: uitvoerkarakter, naar hoofdletter omgezet.
#
# Register gebruik: Geen extra registers. 
# 
####################################################################
#
# toupper(char input)
# {
#    char output;
#    if(input >= 'a' && input <= 'z')
#        output = input - 'a' + 'A';
#    else
#        output = input;
#    return output;
#
####################################################################

toupper:
	blt	$a0, 97, toupper_done			# Kleiner dat 'a'? Niets extra doen.
	bgt	$a0, 122, toupper_done			# Groter dat 'z'? Niets extra doen.
	addi	$a0, $a0, -97				# Ligt tussen 'a' en 'z' -> 'a' aftrekken
	addi	$a0, $a0, 65				#                        -> 'A' optellen
	
toupper_done:
	move	$v0, $a0					# Input naar output kopieren
	jr	$ra								# Terugkeren


####################################################################
