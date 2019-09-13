####################################################################
# 5x5.s
#
# Doel: Een programma dat een 5x5 matrix kan uitprinten, een element in de tabel kan vervangen en 2 tabellen kan vergelijken.
####################################################################
# Input: /
# Output: /
#
# Register gebruik:
# De registers $a0 - $a3 worden gebruikt om functies op te roepen.
# $v0 = Output van functie checkTables
####################################################################
#
# Pseudo-code beschrijving:
# main {
# 	int matrix[5][5];
# 	int matrix2[5][5];
#	int result;
#	
#	writeTable(matrix);
#	insertTable(matrix, 4, 4, 40);
#	writeTable(matrix);
#	result = checkTables(matrix, matrix2);
#
#	if(result == 0)
#		print("De matrices zijn verschillend");
#	else
#		print("De matrices zijn gelijk");
#	
#	return 0;
# }
####################################################################


	.data
matrix:
	.word 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25
matrix2:
	.word 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25
newline:
	.asciiz "\n"
space:
	.asciiz " "
gelijk: 
	.asciiz "\nDe 2 tabellen zijn gelijk.\n"
nietgelijk:
	.asciiz "\nDe 2 tabellen zijn verschillend.\n"


###################### Code Segment ################################

	.text
	.globl main
main:
	la 	$a0, matrix		# Adress van matrix in $a0 laden
	jal 	writeTable		# De matrix uitprinten 
	la 	$a0, matrix
	jal	transpose	
	jal 	writeTable		# De matrix uitprinten
	b 	end			# Branchen naar end


verschillend:
	la 	$a0, nietgelijk		# De string 'nietgelijk' afprinten
	li 	$v0, 4
	syscall
	b 	end			# Branchen naar end
	


end:
	li	$v0, 10
	syscall


####################################################################
# writeTabel functie
#
# Parameters:
# $a0 = Adres van de matrix
#
# Doel: Print een 5x5 matrix af 
####################################################################
# Input: $a0 = Start adres van de matrix
# Output: Geen
#
# Register gebruik:
# $t0 = Teller van de rij
# $t1 = Teller van de kolom
# $t2 = Adress van de matrix(rij, kolom)
# $t3 = Tijdelijke variabele om een vermenigvuldiging in te bewaren
# $t6 = Het adress van de matrix
# $t7 = Grootte van de rijen en kolommen 
# 
####################################################################
#
# void writeTable(int matrix[5][5]) {
#	int i, j;
#
#	for(i = 0; i < 5; i++) {
#		for(j = 0; j < 5; j++) {
#			print(matrix[i][j] + " ");
#		}
#		print("\n");
#	}
####################################################################

writeTable:
	move	$t6, $a0
	li	$t7, 5
	li 	$t0, 0 		#rij
	li	$t1, 0  		#kolom
loop:
	beq 	$t1, $t7, incrementRow
	beq 	$t0, $t7, writeTable_end
	
	mul	$t2, $t0, 4
	mul 	$t2, $t2, 5
	mul 	$t3, $t1, 4
	add	$t2, $t2, $t3
	add	$t2, $t6, $t2
	lb	$a0, ($t2)
	li 	$v0, 1
	syscall
	li 	$v0, 4
	la	$a0, space
	syscall
	addi 	$t1, $t1, 1
	b 	loop
incrementRow:
	addi 	$t0, $t0, 1
	li 	$t1, 0
	la 	$a0, newline
	li 	$v0, 4
	syscall
	b 	loop
writeTable_end:
	la 	$a0, newline
	li 	$v0, 4
	syscall
	jr 	$ra
	
	
insertTable: 
	mul	$t0, $a1, 4
	mul	$t0, $t0, 5
	mul 	$t1, $a2, 4
	add	$t0, $t0, $t1
	add 	$t0, $a0, $t0
	sb	$a3, ($t0)
	jr 	$ra	

checkTables: 
	li 	$t0, 0 
	li 	$t1, 0

checkTables_loop:
	beq 	$t0, 5, equalTables
	beq 	$t1, 5, upRow
	mul 	$t2, $t0, 4
	mul 	$t2, $t2, 5
	mul 	$t3, $t1, 4
	add 	$t2, $t2, $t3
	add 	$t4, $a0, $t2
	add 	$t5, $a1, $t2
	lw	$t4, ($t4)
	lw	$t5, ($t5)
	bne	$t4, $t5, notEqual
	addi 	$t1, $t1, 1
	b 	checkTables_loop
equalTables:
	li 	$v0, 1
	jr 	$ra
notEqual:
	li 	$v0, 0
	jr 	$ra
upRow:
	addi 	$t0, $t0, 1
	li 	$t1, 0
	b 	checkTables_loop
	
	

transpose:
	move 	$t0, $a0
	li	$t1, 0
	li 	$t2, 0
transpose_loop:
	beq	$t1, 5, transpose_end
	beq 	$t2, 5, transpose_incrementRow

	mul 	$t3, $t1, 20
	mul	$t7, $t2, 4
	add	$t3, $t3, $t7

	mul	$t4, $t2, 20
	mul 	$t7, $t1, 4
	add	$t4, $t4, $t7

	add	$t7, $a0, $t3
	add 	$t6, $a0, $t4	
	lw	$t5, 0($t7)
	lw	$t8, 0($t6)
	sw	$t5, 0($t6)
	sw 	$t8, 0($t7)

	addi	$t2, $t2, 1
	b 	transpose_loop

transpose_incrementRow:
	addi 	$t1, $t1, 1
	addi	$t2, $t1, 0
	b 	transpose_loop

transpose_end:
	jr 	$ra



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
