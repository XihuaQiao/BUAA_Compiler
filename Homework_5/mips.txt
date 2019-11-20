.data
string_0: .asciiz "Hello world!"
string_1: .asciiz "%d\n"
.text
la $t7, ($sp)
sub $sp, $sp, 8020
j main
aDd:
sub $sp, $sp, 16
lw $t0, 12($sp)
add $t0, $t0, 0
sw $t0, 4($sp)
lw $t0, 4($sp)
lw $t1, 8($sp)
add $t0, $t0, $t1
sw $t0, 0($sp)
lw $t6, 0($sp)
add $sp, $sp, 16
jr $ra
I:
sub $sp, $sp, 16
lw $t0, 12($sp)
add $t0, $t0, 0
sw $t0, 4($sp)
lw $t0, 4($sp)
add $t0, $t0, 1
sw $t0, 0($sp)
lw $t0, 0($sp)
sw $t0, 8($sp)
lw $t6, 8($sp)
add $sp, $sp, 16
jr $ra
number:
sub $sp, $sp, 0
li $t6, 10
add $sp, $sp, 0
jr $ra
_char:
sub $sp, $sp, 0
li $t6, 'x'
add $sp, $sp, 0
jr $ra
__char:
sub $sp, $sp, 16
lw $t0, 4($sp)
add $t0, $t0, 0
sw $t0, 0($sp)
lw $t0, 0($sp)
li $t1, 0
sub $t2, $t0, $t1
blez $t2, label_0
lw $t6, 12($sp)
add $sp, $sp, 16
jr $ra
j label_1
label_0:
lw $t6, 8($sp)
add $sp, $sp, 16
jr $ra
label_1:
print:
sub $sp, $sp, 0
la $a0, string_0
li $v0, 4
syscall
li, $a0, '\n'
li $v0, 11
syscall
add $sp, $sp, 0
jr $ra
add $sp, $sp, 0
jr $ra
main:
sub $sp, $sp, 44
li $t0, '*'
sw $t0, -8012($t7)
li $t0, '+'
sw $t0, -8016($t7)
jal _char
add $t0, $t6, 0
sw $t0, 40($sp)
lw $t0, 40($sp)
sw $t0, -8020($t7)
li $t0, 'x'
sw $t0, -8008($t7)
li $t0, '+'
sw $t0, -8008($t7)
jal print
li $v0, 5
syscall
sw $v0, -4004($t7)
li $v0, 12
syscall
sw $v0, -8020($t7)
li $t0, 100
sw $t0, -4($sp)
jal I
add $t0, $t6, 0
sw $t0, 36($sp)
li $t0, 10
sw $t0, -4000($t7)
li $t0, 10
sw $t0, -4000($t7)
li $t0, +10
sw $t0, -4($sp)
li $t0, -20
sw $t0, -8($sp)
jal aDd
add $t0, $t6, 0
sw $t0, 32($sp)
la $a0, string_1
li $v0, 4
syscall
lw $a0, 32($sp)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
li $t0, 100
sw $t0, -4($sp)
jal I
add $t0, $t6, 0
sw $t0, 28($sp)
jal number
lw $t0, 28($sp)
add $t0, $t0, $t6
sw $t0, 24($sp)
lw $a0, 24($sp)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
li $t0, 200000
sw $t0, -4($sp)
jal I
add $t0, $t6, 0
sw $t0, 20($sp)
li $t0, -20
sw $t0, -4($sp)
li $t0, +10
sw $t0, -8($sp)
jal aDd
li $t0, 100
sw $t0, -4($sp)
jal I
mult $t6, $t6
mflo $t0
sw $t0, 16($sp)
lw $t0, 20($sp)
lw $t1, 16($sp)
add $t0, $t0, $t1
sw $t0, 12($sp)
add $t0, $0, 0
sw $t0, 8($sp)
lw $t0, 12($sp)
lw $t1, 8($sp)
add $t0, $t0, $t1
sw $t0, 4($sp)
lw $t0, 4($sp)
sw $t0, -4008($t7)
lw $t0, -8012($t7)
sw $t0, -4($sp)
lw $t0, -8016($t7)
sw $t0, -8($sp)
lw $t0, -4004($t7)
sw $t0, -12($sp)
jal __char
add $t0, $t6, 0
sw $t0, 0($sp)
lw $a0, 0($sp)
li $v0, 11
syscall
li, $a0, '\n'
li $v0, 11
syscall
li $v0, 10
syscall
