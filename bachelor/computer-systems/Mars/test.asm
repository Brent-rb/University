####################################################################
	.data
#<Hier komen de gegevensdeclaraties>
array:
	.space 124


###################### Code Segment ################################

	.text
	.globl main

main:
	la 	$a0, array
	la 	$a1, 124
	li 	$v0, 8
	syscall

	li 	$t0, 0
loop:	
	lbu 	$t1, array($t0)
	beq 	$t1, 10, deleteN
	addi 	$t0, $t0, 1
	bnez 	$t1, loop
	jal 	checkPalin
	move 	$a0, $v0
	li 	$v0, 1
	syscall


main_end:
	li 	$v0, 10
	syscall


deleteN:
	li 	$t2, 0
	sb 	$t2, array($t0)
	jal 	checkPalin
	move 	$a0, $v0
	li 	$v0, 1
	syscall
	b 	main_end



checkPalin:
	la	$t0, array
	li 	$t1, 0
checkPalin_loop:
	lbu 	$t3, array($t1)
	beqz 	$t3, checkPalin_foundZero
	addi 	$t1, $t1, 1
	b 	checkPalin_loop

checkPalin_foundZero:
	la 	$t2, array
	add 	$t2, $t2, $t1
	subi 	$t2, $t2, 1
	
	move 	$a0, $t0
	move 	$a1, $t2
	subi 	$sp, $sp, 4
	sw 	$ra, ($sp)
	jal 	checkPalin_recursive
	lw 	$ra, ($sp)
	addi 	$sp, $sp, 4
	jr 	$ra


checkPalin_recursive:
	bge 	$a0, $a1, checkPalin_recursive_endtrue
	lbu 	$t0, ($a0)
	lbu 	$t1, ($a1)
	beq	$t0, $t1, checkPalin_recursive_true
	b 	checkPalin_recursive_false

checkPalin_recursive_true:
	subi 	$sp, $sp, 4
	sw 	$ra, ($sp)
	addi 	$a0, $a0, 1
	subi 	$a1, $a1, 1
	jal 	checkPalin_recursive
	lw 	$ra, ($sp)
	addi 	$sp, $sp, 4
	jr 	$ra

checkPalin_recursive_false:
	li 	$v0, 0
	jr 	$ra

checkPalin_recursive_endtrue:
	li 	$v0, 1
	jr 	$ra
	








