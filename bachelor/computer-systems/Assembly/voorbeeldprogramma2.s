
####################################################################
# Voorbeeldprogramma 2
#
# Doel: 
# Inoefenen van basisinstructies.
# ##################################################################
# Register gebruik
#
# Zie opdrachten
####################################################################
#
# pseudo-code main:
# 
# Zie opdrachten
###################### Data Segment ################################
	.data
getal1:
	.word 10
getal2:
	.word 0
dlbr:
	.asciiz "\n Het is deelbaar door 4. \n"
ndlbr:
	.asciiz "\n Het is niet deelbaar door 4. \n"

###################### Code Segment ################################
	.text
	.globl main
main:
	
	#Schrijf hier je code
	lw 	$t0, getal1
	sw 	$t0, getal2
	addi 	$t1, $t0, 5
	move 	$t2, $t0
	li	$t1, 7
	sub 	$t4, $t2, $t1
	sub 	$t5, $t1, $t2
	addi	$t6, $t5, 0
	li	$v0, 5
	syscall
	move	$s1, $v0
	li	$s2, 4
	rem 	$t7, $s1, $s2
	beqz	$t7, deelbaar
	bnez	$t7, nietdeelbaar
deelbaar:
	li 	$v0, 4
	la 	$a0, dlbr
	syscall
	b 	end
nietdeelbaar:
	li	$v0, 4
	la 	$a0, ndlbr
	syscall
	b 	end

end:	
	li	$v0,10		# system call code voor exit
	syscall			# exit

####################################################################
