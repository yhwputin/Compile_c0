.data
x: .word 0
.text
j main
add:
li $t0,0
move $s1,$fp
move $fp,$sp
addi $fp,$fp,-4
sw $s1,0($fp)
sw $ra,-4($fp)
addi $sp,$sp,-8
li $t1,2
TEP_0:
lw $0,0($sp)
addi $sp,$sp,-4
addi $t0,$t0,1
bne $t0,$t1,TEP_0
la $t8,x
lw $t0,0($t8)
sw $t0,-8($fp)
lw $t0,-8($fp)
li $t1,1
add $t0,$t0,$t1
sw $t0,-12($fp)
lw $t0,-12($fp)
la $t9,x
sw $t0,0($t9)
la $t8,x
lw $t0,0($t8)
sw $t0,-8($fp)
lw $v0,-8($fp)
lw $ra,-4($fp)
addi $sp,$fp,4
lw $fp,0($fp)
jr $ra
main:
li $t0,0
move $s1,$fp
move $fp,$sp
addi $fp,$fp,-4
sw $s1,0($fp)
sw $ra,-4($fp)
addi $sp,$sp,-8
li $t1,3
TEP_1:
lw $0,0($sp)
addi $sp,$sp,-4
addi $t0,$t0,1
bne $t0,$t1,TEP_1
li $t0,0
la $t9,x
sw $t0,0($t9)
la $t8,x
lw $t0,0($t8)
sw $t0,-8($fp)
jal add
move $t0,$v0
sw $t0,-12($fp)
lw $t0,-8($fp)
lw $t1,-12($fp)
add $t0,$t0,$t1
sw $t0,-16($fp)
lw $a0,-16($fp)
li $v0,1
syscall
li $a0,10
li $v0,11
syscall
li $v0,10
syscall
