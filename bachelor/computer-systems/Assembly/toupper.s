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
	.asciiz	"DiT iS eEn test!?\n"

###################### Code Segment ################################
	.text
	.globl main
main:
	
	#Schrijf hier je code

	
	li	$v0, 4		# system call code voor print string
	la	$a0, tekst	# str printen
	syscall			# print
	jal	toupper
	move	$a0, $v0
	li 	$v0, 4
	syscall

	li	$v0,10		# system call code voor exit
	syscall			# exit


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
	move 	$t0, $a0
toupper_loop:
	lbu	$t1, 0($t0)
	beq	$t1, $zero, toupper_done
	blt	$t1, 97, toupper_increment			# Kleiner dat 'a'? Niets extra doen.
	bgt	$t1, 122, toupper_increment			# Groter dat 'z'? Niets extra doen.
	addi	$t1, $t1, -97				# Ligt tussen 'a' en 'z' -> 'a' aftrekken
	addi	$t1, $t1, 65				#                        -> 'A' optellen
	sb	$t1, 0($t0)
toupper_increment:
	addi 	$t0, $t0, 1	
	b	toupper_loop

toupper_done:
	move	$v0, $a0					# Input naar output kopieren
	jr	$ra								# Terugkeren


####################################################################
