####################################################################
# Hoofdletter2plaatsen
#
# Doel: 
# Hoofdletters 2 plaatsen in het alfabet opschuiven
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
#     teken = teken(shift);
#     tekst[positie] = teken;
#     positie++;
#     teken = tekst[positie];
# }
# Print tekst;
###################### Data Segment ################################
	.data
tekst:
	.asciiz	"abcABCDEFGHIJKLMNOPQRSTUVWXYZ"
ask:
	.asciiz "Geef het aantal posities in \n"

###################### Code Segment ################################
	.text
	.globl main
main:
	la	$a0, ask
	li 	$v0, 4
	syscall
	li 	$v0, 5
	syscall
	move	$a1, $v0
	la	$s0, tekst #Het begin adress van de string

loop:
	lb	$s1, ($s0) #De char inlezen
	beqz	$s1, end  #Als het de zero byte is moeten we stoppen
	move	$a0, $s1  #De char meegeven als parameter
	jal	shift	 #De subroutine oproepen
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
# shift
#
# Doel: Verhoog de char met 2 plaatsen in het alfabet als het een hoofdletter is 
####################################################################
# Input: $a0: invoerkarakter
# Output: $v0: uitvoerkarakter, naar hoofdletter omgezet.
#
# Register gebruik: Geen extra registers. 
# 
####################################################################
#
# shift(char input)
# {
#    char output;
#    if(input >= 'A' && input <= 'Z') {
#        output = input + 2;
#    	if(output > 'Z')
#        	output = (output - 'Z') + 'A';
#    }
#    else
#        output = input;
#    return output;
#
####################################################################

shift:
	blt	$a0, 65, shift_done			# Kleiner dat 'A'? Niets extra doen.
	bgt	$a0, 90, shift_done			# Groter dat 'Z'? Niets extra doen.
	add	$a0, $a0, $a1				# 2 letters bijtellen
	ble	$a0, 90, shift_done			# Kleiner of 'Z' --> gedaan
	addi	$a0, $a0, -90				#Z aftrekken
	addi 	$a0, $a0, 64				#A optellen
shift_done:
	move	$v0, $a0					# Input naar output kopieren
	jr	$ra								# Terugkeren


####################################################################
