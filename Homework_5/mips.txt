.data
.text
la $t7, ($sp)
sub $sp, $sp, 400
j main
add:
sub $sp, $sp, 20
lw $t0, 16($sp)
add $t0, $t0, 0
sw $t0, 4($sp)
lw $t0, 4($sp)
lw $t1, 12($sp)
add $t0, $t0, $t1
sw $t0, 0($sp)
lw $t0, 0($sp)
sw $t0, 8($sp)
lw $t6, 8($sp)
add $sp, $sp, 20
jr $ra
fibna:
sub $sp, $sp, 28
lw $t0, 24($sp)
add $t0, $t0, 0
sw $t0, 20($sp)
lw $t0, 20($sp)
sub $t0, $t0, 1
sw $t0, 16($sp)
lw $t5, 16($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
li $t4, 400
sub $t3, $t4, $t3
sub $t3, $t7, $t3
lw $t0, ($t3)
add $t0, $t0, 0
sw $t0, 12($sp)
lw $t0, 24($sp)
add $t0, $t0, 0
sw $t0, 8($sp)
lw $t0, 8($sp)
sub $t0, $t0, 2
sw $t0, 4($sp)
lw $t0, 12($sp)
lw $t5, 4($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
li $t4, 400
sub $t3, $t4, $t3
sub $t3, $t7, $t3
lw $t1, ($t3)
add $t0, $t0, $t1
sw $t0, 0($sp)
lw $t0, 0($sp)
lw $t5, 24($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
li $t4, 400
sub $t3, $t4, $t3
sub $t3, $t7, $t3
sw $t0, ($t3)
add $sp, $sp, 28
jr $ra
main:
sub $sp, $sp, 48
li $t0, 3
sw $t0, 44($sp)
li $t0, 3
sw $t0, 44($sp)
li $t0, 1
sw $t0, -396($t7)
li $t0, 1
sw $t0, -392($t7)
li $t0, 3
sw $t0, 44($sp)
label_0:
lw $t0, 44($sp)
add $t0, $t0, 0
sw $t0, 40($sp)
lw $t0, 40($sp)
li $t1, 15
sub $t2, $t0, $t1
bgez $t2, label_1
lw $t0, 44($sp)
sw $t0, -4($sp)
jal fibna
lw $t0, 44($sp)
add $t0, $t0, 1
sw $t0, 44($sp)
j label_0
label_1:
li $t0, 1
sw $t0, 44($sp)
label_2:
lw $t0, 44($sp)
add $t0, $t0, 0
sw $t0, 36($sp)
lw $t0, 36($sp)
li $t1, 15
sub $t2, $t0, $t1
bgez $t2, label_3
lw $t5, 44($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
li $t4, 400
sub $t3, $t4, $t3
sub $t3, $t7, $t3
lw $t0, ($t3)
add $t0, $t0, 0
sw $t0, 32($sp)
lw $a0, 32($sp)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
lw $t0, 44($sp)
add $t0, $t0, 1
sw $t0, 44($sp)
j label_2
label_3:
li $t0, 1
sw $t0, 44($sp)
label_4:
lw $t0, 44($sp)
add $t0, $t0, 0
sw $t0, 28($sp)
lw $t0, 28($sp)
li $t1, 12
sub $t2, $t0, $t1
bgez $t2, label_5
label_6:
lw $t0, 44($sp)
add $t0, $t0, 0
sw $t0, 24($sp)
lw $t0, 24($sp)
li $t1, 0
sub $t2, $t0, $t1
beq $t2, $0, label_7
lw $t0, 44($sp)
add $t0, $t0, 0
sw $t0, 20($sp)
lw $t0, 20($sp)
sub $t0, $t0, 1
sw $t0, 16($sp)
lw $t0, 16($sp)
sw $t0, 44($sp)
j label_6
label_7:
lw $t0, 44($sp)
add $t0, $t0, 1
sw $t0, 44($sp)
j label_4
label_5:
li $t0, 13
sw $t0, 44($sp)
label_8:
lw $t0, 44($sp)
add $t0, $t0, 0
sw $t0, 12($sp)
lw $t0, 12($sp)
li $t1, 0
sub $t2, $t0, $t1
blez $t2, label_9
lw $t0, 44($sp)
add $t0, $t0, 0
sw $t0, 8($sp)
lw $t0, 8($sp)
sub $t0, $t0, 1
sw $t0, 4($sp)
lw $t0, 4($sp)
sw $t0, 44($sp)
j label_8
label_9:
li $t0, 10
sw $t0, 44($sp)
label_10:
lw $t0, 44($sp)
add $t0, $t0, 0
sw $t0, 0($sp)
lw $t0, 0($sp)
li $t1, 0
sub $t2, $t0, $t1
blez $t2, label_11
lw $t0, 44($sp)
sub $t0, $t0, 1
sw $t0, 44($sp)
j label_10
label_11:
li $v0, 10
syscall
