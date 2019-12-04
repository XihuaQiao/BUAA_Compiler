.data
string_0: .asciiz "testnum[2] = "
string_1: .asciiz "testnum[1] = "
string_2: .asciiz "testnum[3] = "
string_3: .asciiz "testnum[0] = "
g_list: .space 80
testnum: .space 40
.text
j main
abs:
sub $sp, $sp, 36
sw $ra, 32($sp)
lw $t0, g_list + 0
add $t0, $0, $t0
sw $t0, 24($sp)
lw $t0, 24($sp)
add $t0, $t0, 1
sw $t0, 20($sp)
lw $t0, 20($sp)
sw $t0, g_list + 0
lw $t0, 28($sp)
add $t0, $0, $t0
sw $t0, 16($sp)
lw $t0, 16($sp)
li $t1, 0
sub $t2, $t0, $t1
bgez $t2, label_0
lw $t0, 28($sp)
sub $t0, $0, $t0
sw $t0, 12($sp)
lw $t0, 12($sp)
add $t0, $t0, 0
sw $t0, 8($sp)
lw $t6, 8($sp)
lw $ra, 32($sp)
add $sp, $sp, 36
jr $ra
label_0:
lw $t0, 28($sp)
add $t0, $0, $t0
sw $t0, 4($sp)
lw $t0, 4($sp)
add $t0, $t0, 0
sw $t0, 0($sp)
lw $t6, 0($sp)
lw $ra, 32($sp)
add $sp, $sp, 36
jr $ra
init:
sub $sp, $sp, 28
sw $ra, 24($sp)
li $t0, 0
sw $t0, 20($sp)
label_2:
lw $t0, 20($sp)
add $t0, $0, $t0
sw $t0, 16($sp)
lw $t0, 16($sp)
li $t1, 10
sub $t2, $t0, $t1
bgez $t2, label_3
li $t0, 0
lw $t5, 20($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
la $t4, g_list
add $t3, $t4, $t3
sw $t0, ($t3)
lw $t0, 20($sp)
add $t0, $0, $t0
sw $t0, 12($sp)
lw $t0, 12($sp)
add $t0, $t0, 1
sw $t0, 8($sp)
lw $t0, 8($sp)
sw $t0, 20($sp)
j label_2
label_3:
lw $t0, g_list + 4
add $t0, $0, $t0
sw $t0, 4($sp)
lw $t0, 4($sp)
add $t0, $t0, 1
sw $t0, 0($sp)
lw $t0, 0($sp)
sw $t0, g_list + 4
lw $ra, 24($sp)
add $sp, $sp, 28
jr $ra
show:
sub $sp, $sp, 24
sw $ra, 20($sp)
li $t0, 1
sw $t0, g_list + 12
li $t0, 0
sw $t0, 16($sp)
label_4:
lw $t0, 16($sp)
add $t0, $0, $t0
sw $t0, 12($sp)
lw $t0, 12($sp)
li $t1, 4
sub $t2, $t0, $t1
bgez $t2, label_5
lw $t5, 16($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
la $t4, g_list
add $t3, $t4, $t3
lw $t0, ($t3)
add $t0, $0, $t0
sw $t0, 8($sp)
lw $a0, 8($sp)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
lw $t0, 16($sp)
add $t0, $0, $t0
sw $t0, 4($sp)
lw $t0, 4($sp)
add $t0, $t0, 1
sw $t0, 0($sp)
lw $t0, 0($sp)
sw $t0, 16($sp)
j label_4
label_5:
lw $ra, 20($sp)
add $sp, $sp, 24
jr $ra
times:
sub $sp, $sp, 20
sw $ra, 16($sp)
li $t0, 1
sw $t0, g_list + 8
lw $t0, 12($sp)
lw $t1, 8($sp)
mult $t0, $t1
mflo $t0
sw $t0, 4($sp)
lw $t0, 4($sp)
add $t0, $0, $t0
sw $t0, 0($sp)
lw $t6, 0($sp)
lw $ra, 16($sp)
add $sp, $sp, 20
jr $ra
sum4:
sub $sp, $sp, 44
sw $ra, 40($sp)
add $t0, $0, 1
sw $t0, 20($sp)
lw $t0, 20($sp)
lw $t1, g_list + 12
add $t0, $t0, $t1
sw $t0, 16($sp)
lw $t0, 16($sp)
sw $t0, g_list + 12
lw $t0, 36($sp)
add $t0, $0, $t0
sw $t0, 12($sp)
lw $t0, 12($sp)
lw $t1, 32($sp)
add $t0, $t0, $t1
sw $t0, 8($sp)
lw $t0, 8($sp)
lw $t1, 28($sp)
add $t0, $t0, $t1
sw $t0, 4($sp)
lw $t0, 4($sp)
lw $t1, 24($sp)
add $t0, $t0, $t1
sw $t0, 0($sp)
lw $t6, 0($sp)
lw $ra, 40($sp)
add $sp, $sp, 44
jr $ra
fi:
sub $sp, $sp, 64
sw $ra, 60($sp)
lw $t0, 56($sp)
li $t1, 0
sub $t2, $t0, $t1
beq $t2, $0, label_6
lw $t0, 56($sp)
add $t0, $0, $t0
sw $t0, 52($sp)
lw $t0, 52($sp)
add $t0, $t0, 1
sw $t0, 48($sp)
lw $t5, 48($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
la $t4, testnum
add $t3, $t4, $t3
lw $t0, ($t3)
add $t0, $0, $t0
sw $t0, 44($sp)
lw $t0, 56($sp)
add $t0, $0, $t0
sw $t0, 40($sp)
lw $t0, 40($sp)
sub $t0, $t0, -2
sw $t0, 36($sp)
lw $t0, 44($sp)
lw $t5, 36($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
la $t4, testnum
add $t3, $t4, $t3
lw $t1, ($t3)
add $t0, $t0, $t1
sw $t0, 32($sp)
lw $t0, 32($sp)
lw $t5, 56($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
la $t4, testnum
add $t3, $t4, $t3
sw $t0, ($t3)
lw $t0, 56($sp)
add $t0, $0, $t0
sw $t0, 28($sp)
lw $t0, 28($sp)
sub $t0, $t0, 1
sw $t0, 24($sp)
lw $t0, 24($sp)
sw $t0, -8($sp)
jal fi
j label_7
label_6:
lw $t0, 56($sp)
add $t0, $0, $t0
sw $t0, 20($sp)
lw $t0, 20($sp)
add $t0, $t0, 1
sw $t0, 16($sp)
lw $t5, 16($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
la $t4, testnum
add $t3, $t4, $t3
lw $t0, ($t3)
add $t0, $0, $t0
sw $t0, 12($sp)
lw $t0, 56($sp)
add $t0, $0, $t0
sw $t0, 8($sp)
lw $t0, 8($sp)
sub $t0, $t0, -2
sw $t0, 4($sp)
lw $t0, 12($sp)
lw $t5, 4($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
la $t4, testnum
add $t3, $t4, $t3
lw $t1, ($t3)
add $t0, $t0, $t1
sw $t0, 0($sp)
lw $t0, 0($sp)
lw $t5, 56($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
la $t4, testnum
add $t3, $t4, $t3
sw $t0, ($t3)
lw $ra, 60($sp)
add $sp, $sp, 64
jr $ra
label_7:
lw $ra, 60($sp)
add $sp, $sp, 64
jr $ra
main:
sub $sp, $sp, 196
sw $ra, 192($sp)
li $v0, 12
syscall
sw $v0, 176($sp)
li $v0, 5
syscall
sw $v0, 188($sp)
jal init
add $t0, $0, -2
sw $t0, 172($sp)
li $t0, 2
sw $t0, -8($sp)
lw $t0, 172($sp)
sw $t0, -12($sp)
jal times
add $t0, $0, $t6
sw $t0, 168($sp)
lw $t0, 168($sp)
sw $t0, -8($sp)
jal abs
add $t0, $0, $t6
sw $t0, 164($sp)
add $t0, $0, -1
sw $t0, 160($sp)
lw $t0, 160($sp)
sw $t0, -8($sp)
jal abs
add $t0, $0, $t6
sw $t0, 156($sp)
add $t0, $0, -3
sw $t0, 152($sp)
lw $t0, 152($sp)
sw $t0, -8($sp)
jal abs
add $t0, $0, $t6
sw $t0, 148($sp)
li $t0, 22
sw $t0, -8($sp)
jal abs
add $t0, $0, $t6
sw $t0, 144($sp)
lw $t0, 164($sp)
sw $t0, -8($sp)
lw $t0, 156($sp)
sw $t0, -12($sp)
lw $t0, 148($sp)
sw $t0, -16($sp)
lw $t0, 144($sp)
sw $t0, -20($sp)
jal sum4
add $t0, $0, $t6
sw $t0, 140($sp)
lw $a0, 140($sp)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
li $t0, 1
sw $t0, testnum + 36
add $t0, $0, 7
sw $t0, 136($sp)
lw $t0, 136($sp)
add $t0, $t0, 98
sw $t0, 132($sp)
lw $t0, 132($sp)
sub $t0, $t0, 97
sw $t0, 128($sp)
li $t0, 2
lw $t5, 128($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
la $t4, testnum
add $t3, $t4, $t3
sw $t0, ($t3)
li $t0, 7
sw $t0, -8($sp)
jal fi
lw $t0, testnum + 32
add $t0, $0, $t0
sw $t0, 124($sp)
lw $t5, 124($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
la $t4, testnum
add $t3, $t4, $t3
lw $t0, ($t3)
add $t0, $0, $t0
sw $t0, 120($sp)
la $a0, string_0
li $v0, 4
syscall
lw $a0, 120($sp)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
lw $t0, testnum + 4
add $t0, $0, $t0
sw $t0, 116($sp)
la $a0, string_1
li $v0, 4
syscall
lw $a0, 116($sp)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
lw $t0, testnum + 20
add $t0, $0, $t0
sw $t0, 112($sp)
lw $t5, 112($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
la $t4, testnum
add $t3, $t4, $t3
lw $t0, ($t3)
add $t0, $0, $t0
sw $t0, 108($sp)
lw $t0, 108($sp)
lw $t1, testnum + 36
add $t0, $t0, $t1
sw $t0, 104($sp)
lw $t5, 104($sp)
li $t3, 4
mult $t3, $t5
mflo $t3
la $t4, testnum
add $t3, $t4, $t3
lw $t0, ($t3)
add $t0, $0, $t0
sw $t0, 100($sp)
la $a0, string_2
li $v0, 4
syscall
lw $a0, 100($sp)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
lw $t0, testnum + 0
add $t0, $0, $t0
sw $t0, 96($sp)
la $a0, string_3
li $v0, 4
syscall
lw $a0, 96($sp)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
li $t0, 0
sw $t0, 184($sp)
lw $t0, 188($sp)
add $t0, $0, $t0
sw $t0, 92($sp)
lw $t0, 92($sp)
li $t1, 10
sub $t2, $t0, $t1
blez $t2, label_8
li $t0, 0
sw $t0, 180($sp)
label_10:
lw $t0, 184($sp)
add $t0, $0, $t0
sw $t0, 88($sp)
lw $t0, 88($sp)
lw $t1, 180($sp)
add $t0, $t0, $t1
sw $t0, 84($sp)
lw $t0, 84($sp)
sw $t0, 184($sp)
lw $t0, 180($sp)
add $t0, $0, $t0
sw $t0, 80($sp)
lw $t0, 80($sp)
add $t0, $t0, 1
sw $t0, 76($sp)
lw $t0, 76($sp)
sw $t0, 180($sp)
lw $t0, 180($sp)
add $t0, $0, $t0
sw $t0, 72($sp)
lw $t0, 72($sp)
lw $t1, 188($sp)
sub $t2, $t0, $t1
bltz $t2, label_10
j label_9
label_8:
lw $t0, 176($sp)
add $t0, $0, $t0
sw $t0, 68($sp)
lw $t0, 68($sp)
add $t0, $t0, 0
sw $t0, 64($sp)
add $t0, $0, 43
sw $t0, 60($sp)
lw $t0, 60($sp)
add $t0, $t0, 0
sw $t0, 56($sp)
lw $t0, 64($sp)
lw $t1, 56($sp)
sub $t2, $t0, $t1
bne $t2, $0, label_11
li $t0, 0
sw $t0, 180($sp)
label_13:
lw $t0, 180($sp)
add $t0, $0, $t0
sw $t0, 52($sp)
lw $t0, 188($sp)
add $t0, $0, $t0
sw $t0, 48($sp)
lw $t0, 48($sp)
add $t0, $t0, 3
sw $t0, 44($sp)
lw $t0, 52($sp)
lw $t1, 44($sp)
sub $t2, $t0, $t1
bgez $t2, label_14
lw $t0, 184($sp)
add $t0, $0, $t0
sw $t0, 40($sp)
lw $t0, 40($sp)
lw $t1, 180($sp)
add $t0, $t0, $t1
sw $t0, 36($sp)
lw $t0, 36($sp)
sw $t0, 184($sp)
lw $t0, 180($sp)
add $t0, $0, $t0
sw $t0, 32($sp)
lw $t0, 32($sp)
add $t0, $t0, 3
sw $t0, 28($sp)
lw $t0, 28($sp)
sw $t0, 180($sp)
j label_13
label_14:
j label_12
label_11:
li $t0, 0
sw $t0, 180($sp)
label_15:
lw $t0, 180($sp)
add $t0, $0, $t0
sw $t0, 24($sp)
lw $t0, 188($sp)
add $t0, $0, $t0
sw $t0, 20($sp)
lw $t0, 20($sp)
add $t0, $t0, 3
sw $t0, 16($sp)
lw $t0, 24($sp)
lw $t1, 16($sp)
sub $t2, $t0, $t1
bgez $t2, label_16
lw $t0, 184($sp)
add $t0, $0, $t0
sw $t0, 12($sp)
lw $t0, 12($sp)
lw $t1, 180($sp)
sub $t0, $t0, $t1
sw $t0, 8($sp)
lw $t0, 8($sp)
sw $t0, 184($sp)
lw $t0, 180($sp)
add $t0, $0, $t0
sw $t0, 4($sp)
lw $t0, 4($sp)
add $t0, $t0, 3
sw $t0, 0($sp)
lw $t0, 0($sp)
sw $t0, 180($sp)
j label_15
label_16:
label_12:
label_9:
jal show
lw $a0, 184($sp)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
li $v0, 10
syscall
