####################################################################
	.data
#<Hier komen de gegevensdeclaraties>

askchar:
	.asciiz "Geef een character in: "

newline:
	.asciiz "\n"
gelijk:
	.asciiz "\nDe letter is in de zin gevonden.\n"
verschillend:
	.asciiz "\nDe letter is niet in de zin gevonden.\n"

testzin:
	.asciiz "Dit is een testzin.\n"


###################### Code Segment ################################

	.text
	.globl main
main:
	li 	$v0, 4
	la 	$a0, askchar
	syscall
	li 	$v0, 12
	syscall
	move 	$a0, $v0
	la 	$a1, testzin
	li 	$a2, 20
	jal 	countChars
	beq 	$v0, -1, print_verschillend
	b 	print_gelijk
main_end:
	li 	$v0, 10
	syscall
	

print_gelijk:
	move 	$t0, $v0
	
	li 	$v0, 1
	move 	$a0, $t0
	syscall
	b 	main_end
print_verschillend:
	li 	$v0, 4
	la 	$a0, verschillend
	syscall
	b 	main_end




#############################################################
		      #Subroutines#
#############################################################




checkChars:
	move	$t0, $a0
	move 	$t1, $a1
	bgt 	$t0, 90, checkChars_checkT1
	blt 	$t0, 65, checkChars_checkT1
	subi 	$t0, $t0, 65
	addi 	$t0, $t0, 97
checkChars_checkT1:
	bgt	$t1, 90, checkChars_checkBoth
	blt	$t1, 65, checkChars_checkBoth
	subi 	$t1, $t1, 65
	addi 	$t1, $t1, 97
checkChars_checkBoth:
	beq 	$t1, $t0, checkChars_equal
	b 	checkChars_different

checkChars_equal:
	li 	$v0, 1
	jr 	$ra
checkChars_different:
	li 	$v0, 0
	jr 	$ra





searchChar:
	move 	$t0, $a1
	move 	$t1, $a2
	subi 	$sp, $sp, 4
	sw	$ra, ($sp)
searchChar_loop:
	beqz 	$t1, searchChar_noFound
	lbu 	$a1, ($t0)	
	subi 	$sp, $sp, 4
	sw 	$t0, ($sp)
	subi 	$sp, $sp, 4
	sw 	$t1, ($sp)
	jal 	checkChars
	beq 	$v0, 1, searchChar_found
	lw 	$t1, ($sp)
	subi 	$t1, $t1, 1
	addi 	$sp, $sp, 4
	lw 	$t0, ($sp)
	addi 	$t0, $t0, 1
	addi 	$sp, $sp, 4
	b 	searchChar_loop


searchChar_noFound:
	li 	$v0, -1
	b 	searchChar_end
searchChar_found:
	addi	$sp, $sp, 4
	lw 	$v0, ($sp)
	addi 	$sp, $sp, 4
searchChar_end:
	lw 	$ra, ($sp)
	addi 	$sp, $sp, 4
	jr 	$ra




countChars:
	move 	$t0, $a0
	move	$t1, $a1
	move 	$t2, $a2
	move 	$t4, $t1
	li 	$t3, 0
	subi 	$sp, $sp, 4
	sw 	$ra, ($sp)

countChars_loop:
	move 	$a0, $t0
	move 	$a1, $t4
	move 	$a2, $t2
	subi 	$sp, $sp, 4
	sw 	$t0, ($sp)
	subi 	$sp, $sp, 4
	sw 	$t1, ($sp)
	subi 	$sp, $sp, 4
	sw 	$t2, ($sp)
	subi 	$sp, $sp, 4
	sw 	$t3, ($sp)
	jal 	searchChar
	lw 	$t3, ($sp)
	addi 	$sp, $sp, 4
	lw 	$t2, ($sp)
	addi 	$sp, $sp, 4
	lw 	$t1, ($sp)
	addi 	$sp, $sp, 4
	lw 	$t0, ($sp)
	addi 	$sp, $sp, 4
	beq 	$v0, -1, countChars_end
	
	addi 	$t3, $t3, 1
	sub 	$t5, $v0, $t1
	sub 	$t2, $t2, $t5
	subi 	$t2, $t2, 1
	addi 	$t4, $v0, 1
	b 	countChars_loop

countChars_end:
	addi 	$v0, $t3, 0
	lw 	$ra, ($sp)
	addi 	$sp, $sp, 4
	jr 	$ra
	
	
	
	
	












