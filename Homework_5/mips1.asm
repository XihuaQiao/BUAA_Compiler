.data
.text
la $t7, ($sp)
sub $sp, $sp, 8
j main
add:
sub $sp, $sp, 24
lw $t0, 20($sp)
add $t0, $t0, 0
sw $t0, 12($sp)
lw $t0, 12($sp)
lw $t1, 16($sp)
add $t0, $t0, $t1
sw $t0, 8($sp)
lw $t0, 8($sp)
sw $t0, 20($sp)
lw $t0, 20($sp)
add $t0, $t0, 0
sw $t0, 4($sp)
lw $t0, 4($sp)
lw $t1, 16($sp)
add $t0, $t0, $t1
sw $t0, 0($sp)
lw $t6, 0($sp)
add $sp, $sp, 24
jr $ra
main:
sub $sp, $sp, 4
li $t0, 3
sw $t0, -4($t7)
li $t0, 'a'
sw $t0, -8($t7)
lw $t0, -4($t7)
sw $t0, -4($sp)
lw $t0, -8($t7)
sw $t0, -8($sp)
jal add
add $t0, $t6, 0
sw $t0, 0($sp)
lw $a0, 0($sp)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
lw $a0, -4($t7)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
lw $a0, -8($t7)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
li $v0, 10
syscall
