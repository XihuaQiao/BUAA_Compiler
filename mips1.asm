.data
string_0: .asciiz "x = "
string_1: .asciiz "y = "
string_2: .asciiz "SWAP x = "
string_3: .asciiz "SWAP y = "
string_4: .asciiz "OVERFLOW!"
string_5: .asciiz "complete number: "
string_6: .asciiz "  "
string_7: .asciiz " "
string_8: .asciiz "---------------------------------------------------------------"
string_9: .asciiz "'water flower'number is:"
string_10: .asciiz "  "
string_11: .asciiz " "
string_12: .asciiz "---------------------------------------------------------------"
string_13: .asciiz " "
string_14: .asciiz " "
string_15: .asciiz "The total is "
string_16: .asciiz "5 != "
.text
j main
factorial:
sub $sp, $sp, 28
sw $ra, 24($sp)
lw $t5, 20($sp)
li $t1, 1
sub $t0, $t5, $t1
bgtz $t0, label_0
li $v0, 1
lw $ra, 24($sp)
add $sp, $sp, 28
jr $ra
label_0:
sub $t4, $t5, 1
sub $sp, $sp, 4
sw $t4, ($sp)
sub $sp, $sp, 4
sw $t5, ($sp)
sw $t4, -8($sp)
jal factorial
lw $t5, ($sp)
add $sp, $sp, 4
lw $t4, ($sp)
add $sp, $sp, 4
mult $t5, $v0
mflo $t4
move $v0, $t4
lw $ra, 24($sp)
add $sp, $sp, 28
jr $ra
main:
sub $sp, $sp, 992
sw $ra, 988($sp)
sub $sp, $sp, 4
sw $t4, ($sp)
sub $sp, $sp, 4
sw $t5, ($sp)
li $t0, 5
sw $t0, -8($sp)
jal factorial
lw $t5, ($sp)
add $sp, $sp, 4
lw $t4, ($sp)
add $sp, $sp, 4
move $t7, $v0
la $a0, string_16
li $v0, 4
syscall
move $a0, $t7
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
li $t6, 5
li $t5, 10
la $a0, string_0
li $v0, 4
syscall
move $a0, $t6
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
la $a0, string_1
li $v0, 4
syscall
move $a0, $t5
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
move $t4, $t6
move $t6, $t5
move $t5, $t4
la $a0, string_2
li $v0, 4
syscall
move $a0, $t6
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
la $a0, string_3
li $v0, 4
syscall
move $a0, $t5
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
li $t0, 2
sw $t0, 448($sp)
_complete_flower_num_0_label_2:
lw $t0, 448($sp)
li $t1, 128
sub $t0, $t0, $t1
bgez $t0, _complete_flower_num_0_label_3
li $t0, -1
sw $t0, 444($sp)
lw $s1, 448($sp)
li $t0, 1
sw $t0, 452($sp)
_complete_flower_num_0_label_4:
lw $t0, 452($sp)
lw $t1, 448($sp)
sub $t0, $t0, $t1
bgez $t0, _complete_flower_num_0_label_5
lw $t0, 448($sp)
lw $t1, 452($sp)
div $t0, $t1
mflo $s0
lw $t1, 452($sp)
mult $s0, $t1
mflo $t9
lw $t8, 448($sp)
lw $t7, 452($sp)
div $t8, $t7
mflo $t6
mult $t6, $t7
mflo $t5
sub $t8, $t8, $t5
move $t4, $t8
bnez $t4, _complete_flower_num_0_label_9
lw $t0, 444($sp)
add $t0, $t0, 1
sw $t0, 444($sp)
lw $t1, 452($sp)
sub $s1, $s1, $t1
lw $t0, 444($sp)
li $t1, 128
sub $t0, $t0, $t1
bltz $t0, _complete_flower_num_0_label_8
la $a0, string_4
li $v0, 4
syscall
li $a0, '\n'
li $v0, 11
syscall
j _complete_flower_num_0_label_9
_complete_flower_num_0_label_8:
lw $t0, 452($sp)
lw $t2, 444($sp)
sll $t2, $t2, 2
add $t2, $t2, 456
add $t2, $t2, $sp
sw $t0, ($t2)
_complete_flower_num_0_label_9:
lw $t0, 452($sp)
add $t0, $t0, 1
sw $t0, 452($sp)
j _complete_flower_num_0_label_4
_complete_flower_num_0_label_5:
bnez $s1, _complete_flower_num_0_label_10
la $a0, string_5
li $v0, 4
syscall
lw $a0, 448($sp)
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
li $t0, 0
sw $t0, 452($sp)
_complete_flower_num_0_label_12:
lw $t0, 452($sp)
lw $t1, 444($sp)
sub $t0, $t0, $t1
bgtz $t0, _complete_flower_num_0_label_13
lw $t2, 452($sp)
sll $t2, $t2, 2
add $t2, $t2, 456
add $t2, $t2, $sp
lw $s2, ($t2)
la $a0, string_6
li $v0, 4
syscall
move $a0, $s2
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
lw $t0, 452($sp)
add $t0, $t0, 1
sw $t0, 452($sp)
j _complete_flower_num_0_label_12
_complete_flower_num_0_label_13:
la $a0, string_7
li $v0, 4
syscall
li $a0, '\n'
li $v0, 11
syscall
_complete_flower_num_0_label_10:
lw $t0, 448($sp)
add $t0, $t0, 1
sw $t0, 448($sp)
j _complete_flower_num_0_label_2
_complete_flower_num_0_label_3:
la $a0, string_8
li $v0, 4
syscall
li $a0, '\n'
li $v0, 11
syscall
la $a0, string_9
li $v0, 4
syscall
li $a0, '\n'
li $v0, 11
syscall
li $t0, 0
sw $t0, 432($sp)
li $t0, 100
sw $t0, 452($sp)
_complete_flower_num_0_label_14:
lw $t0, 452($sp)
li $t1, 228
sub $t0, $t0, $t1
bgez $t0, _complete_flower_num_0_label_15
lw $t0, 452($sp)
la $t1, 100
div $t0, $t1
mflo $t0
sw $t0, 444($sp)
lw $t0, 452($sp)
la $t1, 10
div $t0, $t1
mflo $t0
sw $t0, 308($sp)
lw $t0, 308($sp)
sw $t0, 152($sp)
li $t0, 10
sw $t0, 148($sp)
lw $t0, 152($sp)
lw $t1, 148($sp)
div $t0, $t1
mflo $t0
sw $t0, 164($sp)
lw $t0, 164($sp)
lw $t1, 148($sp)
mult $t0, $t1
mflo $t0
sw $t0, 160($sp)
lw $t0, 152($sp)
lw $t1, 160($sp)
sub $t0, $t0, $t1
sw $t0, 152($sp)
lw $t0, 152($sp)
sw $t0, 448($sp)
lw $t0, 452($sp)
sw $t0, 124($sp)
li $t0, 10
sw $t0, 120($sp)
lw $t0, 124($sp)
lw $t1, 120($sp)
div $t0, $t1
mflo $t0
sw $t0, 136($sp)
lw $t0, 136($sp)
lw $t1, 120($sp)
mult $t0, $t1
mflo $t0
sw $t0, 132($sp)
lw $t0, 124($sp)
lw $t1, 132($sp)
sub $t0, $t0, $t1
sw $t0, 124($sp)
lw $t0, 124($sp)
sw $t0, 408($sp)
lw $t0, 444($sp)
sw $t0, 92($sp)
lw $t0, 448($sp)
sw $t0, 88($sp)
lw $t0, 408($sp)
sw $t0, 84($sp)
lw $t0, 92($sp)
la $t1, 100
mult $t0, $t1
mflo $t0
sw $t0, 112($sp)
lw $t0, 88($sp)
la $t1, 10
mult $t0, $t1
mflo $a3
lw $t0, 112($sp)
add $a2, $t0, $a3
lw $t1, 84($sp)
add $s7, $a2, $t1
move $s6, $s7
lw $s5, 444($sp)
lw $s4, 448($sp)
lw $s3, 408($sp)
mult $s5, $s5
mflo $s2
mult $s2, $s5
mflo $s1
mult $s4, $s4
mflo $s0
mult $s0, $s4
mflo $t9
add $t8, $s1, $t9
mult $s3, $s3
mflo $t7
mult $t7, $s3
mflo $t6
add $t5, $t8, $t6
move $t4, $t5
sub $t0, $s6, $t4
bnez $t0,_complete_flower_num_0_label_16
lw $t0, 452($sp)
lw $t2, 432($sp)
sll $t2, $t2, 2
add $t2, $t2, 456
add $t2, $t2, $sp
sw $t0, ($t2)
lw $t0, 432($sp)
add $t0, $t0, 1
sw $t0, 432($sp)
_complete_flower_num_0_label_16:
lw $t0, 452($sp)
add $t0, $t0, 1
sw $t0, 452($sp)
j _complete_flower_num_0_label_14
_complete_flower_num_0_label_15:
li $t0, 0
sw $t0, 452($sp)
_complete_flower_num_0_label_18:
lw $t0, 452($sp)
lw $t1, 432($sp)
sub $t0, $t0, $t1
bgez $t0, _complete_flower_num_0_label_19
lw $t2, 452($sp)
sll $t2, $t2, 2
add $t2, $t2, 456
add $t2, $t2, $sp
lw $t0, ($t2)
sw $t0, 272($sp)
la $a0, string_10
li $v0, 4
syscall
lw $a0, 272($sp)
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
lw $t0, 452($sp)
add $t0, $t0, 1
sw $t0, 452($sp)
j _complete_flower_num_0_label_18
_complete_flower_num_0_label_19:
la $a0, string_11
li $v0, 4
syscall
li $a0, '\n'
li $v0, 11
syscall
la $a0, string_12
li $v0, 4
syscall
li $a0, '\n'
li $v0, 11
syscall
li $s3, 0
li $s2, 1
li $s4, 2
_complete_flower_num_0_label_20:
li $t1, 128
sub $t0, $s4, $t1
bgtz $t0, _complete_flower_num_0_label_21
la $t1, 2
div $s4, $t1
mflo $s1
li $t0, 2
sw $t0, 452($sp)
_complete_flower_num_0_label_22:
lw $t0, 452($sp)
sub $t0, $t0, $s1
bgtz $t0, _complete_flower_num_0_label_23
lw $t1, 452($sp)
div $s4, $t1
mflo $s0
lw $t1, 452($sp)
mult $s0, $t1
mflo $t9
move $t8, $s4
lw $t7, 452($sp)
div $t8, $t7
mflo $t6
mult $t6, $t7
mflo $t5
sub $t8, $t8, $t5
move $t4, $t8
bnez $t4, _complete_flower_num_0_label_24
li $s2, 0
_complete_flower_num_0_label_24:
lw $t0, 452($sp)
add $t0, $t0, 1
sw $t0, 452($sp)
j _complete_flower_num_0_label_22
_complete_flower_num_0_label_23:
li $t1, 1
sub $t0, $s2, $t1
bnez $t0,_complete_flower_num_0_label_28
la $a0, string_13
li $v0, 4
syscall
move $a0, $s4
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
add $s3, $s3, 1
la $t1, 10
div $s3, $t1
mflo $t4
la $t1, 10
mult $t4, $t1
mflo $t9
sub $t0, $t9, $s3
bnez $t0,_complete_flower_num_0_label_28
la $a0, string_14
li $v0, 4
syscall
li $a0, '\n'
li $v0, 11
syscall
_complete_flower_num_0_label_28:
li $s2, 1
add $s4, $s4, 1
j _complete_flower_num_0_label_20
_complete_flower_num_0_label_21:
la $a0, string_15
li $v0, 4
syscall
move $a0, $s3
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
li $v0, 10
syscall
