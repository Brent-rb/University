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
	.asciiz	"diT iS eEn test!?"

###################### Code Segment ################################
	.text
	.globl main
main:
	la	$s0, tekst #Het begin adress van de string

loop:
	lb	$s1, ($s0) #De char inlezen
	beqz	$s1, end  #Als het de zero byte is moeten we stoppen
	move	$a0, $s1  #De char meegeven als parameter
	jal	toupper	 #De subroutine oproepen
	sb 	$v0, ($s0) #Het antwoord van de subroutine in de string opslagen
	addi	$s0, $s0, 1 #Adress + 1
	b 	loop       #Loop herhalen
 
end:
	la	$a0, tekst
	li 	$v0, 4
	syscall			# print

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
	blt	$a0, 97, toupper_done			# Kleiner dat 'a'? Niets extra doen.
	bgt	$a0, 122, toupper_done			# Groter dat 'z'? Niets extra doen.
	addi	$a0, $a0, -97				# Ligt tussen 'a' en 'z' -> 'a' aftrekken
	addi	$a0, $a0, 65				#                        -> 'A' optellen
	
toupper_done:
	move	$v0, $a0					# Input naar output kopieren
	jr	$ra								# Terugkeren


####################################################################
