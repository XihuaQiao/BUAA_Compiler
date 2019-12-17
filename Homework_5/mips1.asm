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
mod:
sub $sp, $sp, 28
sw $ra, 24($sp)
lw $t7, 20($sp)
lw $t6, 16($sp)
div $t7, $t6
mflo $t5
mult $t5, $t6
mflo $t4
sub $t7, $t7, $t4
move $v0, $t7
lw $ra, 24($sp)
add $sp, $sp, 28
jr $ra
swap:
sub $sp, $sp, 16
sw $ra, 12($sp)
lw $t6, 8($sp)
lw $t5, 4($sp)
la $a0, string_0
li $v0, 4
syscall
move $a0, $t6
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
la $a0, string_1
li $v0, 4
syscall
move $a0, $t5
li $v0, 1
syscall
li, $a0, '\n'
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
li, $a0, '\n'
li $v0, 11
syscall
la $a0, string_3
li $v0, 4
syscall
move $a0, $t5
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
lw $ra, 12($sp)
add $sp, $sp, 16
jr $ra
full_num:
sub $sp, $sp, 36
sw $ra, 32($sp)
lw $s0, 28($sp)
lw $t9, 24($sp)
lw $t8, 20($sp)
la $t1, 100
mult $s0, $t1
mflo $t7
la $t1, 10
mult $t9, $t1
mflo $t6
add $t5, $t7, $t6
add $t4, $t5, $t8
move $v0, $t4
lw $ra, 32($sp)
add $sp, $sp, 36
jr $ra
flower_num:
sub $sp, $sp, 52
sw $ra, 48($sp)
lw $s4, 44($sp)
lw $s3, 40($sp)
lw $s2, 36($sp)
mult $s4, $s4
mflo $s1
mult $s1, $s4
mflo $s0
mult $s3, $s3
mflo $t9
mult $t9, $s3
mflo $t8
add $t7, $s0, $t8
mult $s2, $s2
mflo $t6
mult $t6, $s2
mflo $t5
add $t4, $t7, $t5
move $v0, $t4
lw $ra, 48($sp)
add $sp, $sp, 52
jr $ra
complete_flower_num:
sub $sp, $sp, 964
sw $ra, 960($sp)
li $t0, 2
sw $t0, 440($sp)
label_2:
lw $t0, 440($sp)
li $t1, 128
sub $t0, $t0, $t1
bgez $t0, label_3
li $t0, -1
sw $t0, 436($sp)
lw $s1, 440($sp)
li $t0, 1
sw $t0, 444($sp)
label_4:
lw $t0, 444($sp)
lw $t1, 440($sp)
sub $t0, $t0, $t1
bgez $t0, label_5
lw $t0, 440($sp)
lw $t1, 444($sp)
div $t0, $t1
mflo $t9
lw $t1, 444($sp)
mult $t9, $t1
mflo $t8
lw $t7, 440($sp)
lw $t6, 444($sp)
div $t7, $t6
mflo $t5
mult $t5, $t6
mflo $t4
sub $t7, $t7, $t4
move $s0, $t7
j _mod_0
_mod_0:
move $t4, $s0
bnez $t4, label_9
lw $t0, 436($sp)
add $t0, $t0, 1
sw $t0, 436($sp)
lw $t1, 444($sp)
sub $s1, $s1, $t1
lw $t0, 436($sp)
li $t1, 128
sub $t0, $t0, $t1
bltz $t0, label_8
la $a0, string_4
li $v0, 4
syscall
li, $a0, '\n'
li $v0, 11
syscall
j label_9
label_8:
lw $t0, 444($sp)
lw $t2, 436($sp)
sll $t2, $t2, 2
add $t2, $t2, 448
add $t2, $t2, $sp
sw $t0, ($t2)
label_9:
lw $t0, 444($sp)
add $t0, $t0, 1
sw $t0, 444($sp)
j label_4
label_5:
bnez $s1, label_10
la $a0, string_5
li $v0, 4
syscall
lw $a0, 440($sp)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
li $t0, 0
sw $t0, 444($sp)
label_12:
lw $t0, 444($sp)
lw $t1, 436($sp)
sub $t0, $t0, $t1
bgtz $t0, label_13
lw $t2, 444($sp)
sll $t2, $t2, 2
add $t2, $t2, 448
add $t2, $t2, $sp
lw $t0, ($t2)
add $t4, $0, $t0
la $a0, string_6
li $v0, 4
syscall
lw $t2, 444($sp)
sll $t2, $t2, 2
add $t2, $t2, 448
add $t2, $t2, $sp
lw $a0, ($t2)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
lw $t0, 444($sp)
add $t0, $t0, 1
sw $t0, 444($sp)
j label_12
label_13:
la $a0, string_7
li $v0, 4
syscall
li, $a0, '\n'
li $v0, 11
syscall
label_10:
lw $t0, 440($sp)
add $t0, $t0, 1
sw $t0, 440($sp)
j label_2
label_3:
la $a0, string_8
li $v0, 4
syscall
li, $a0, '\n'
li $v0, 11
syscall
la $a0, string_9
li $v0, 4
syscall
li, $a0, '\n'
li $v0, 11
syscall
li $a3, 0
li $t0, 100
sw $t0, 444($sp)
label_14:
lw $t0, 444($sp)
li $t1, 228
sub $t0, $t0, $t1
bgez $t0, label_15
lw $t0, 444($sp)
la $t1, 100
div $t0, $t1
mflo $t0
sw $t0, 436($sp)
lw $t0, 444($sp)
la $t1, 10
div $t0, $t1
mflo $t8
move $t7, $t8
li $t6, 10
div $t7, $t6
mflo $t5
mult $t5, $t6
mflo $t4
sub $t7, $t7, $t4
move $t9, $t7
j _mod_1
_mod_1:
sw $t9, 440($sp)
lw $t7, 444($sp)
li $t6, 10
div $t7, $t6
mflo $t5
mult $t5, $t6
mflo $t4
sub $t7, $t7, $t4
move $s1, $t7
j _mod_2
_mod_2:
move $s7, $s1
lw $s0, 436($sp)
lw $t9, 440($sp)
move $t8, $s7
la $t1, 100
mult $s0, $t1
mflo $t7
la $t1, 10
mult $t9, $t1
mflo $t6
add $t5, $t7, $t6
add $t4, $t5, $t8
move $a2, $t4
j _full_num_3
_full_num_3:
move $s5, $a2
lw $s4, 436($sp)
lw $s3, 440($sp)
move $s2, $s7
mult $s4, $s4
mflo $s1
mult $s1, $s4
mflo $s0
mult $s3, $s3
mflo $t9
mult $t9, $s3
mflo $t8
add $t7, $s0, $t8
mult $s2, $s2
mflo $t6
mult $t6, $s2
mflo $t5
add $t4, $t7, $t5
move $s6, $t4
j _flower_num_4
_flower_num_4:
move $t4, $s6
sub $t0, $s5, $t4
bnez $t0,label_16
lw $t0, 444($sp)
lw $t2, 424($sp)
sll $t2, $t2, 2
add $t2, $t2, 448
add $t2, $t2, $sp
sw $t0, ($t2)
add $a3, $a3, 1
label_16:
lw $t0, 444($sp)
add $t0, $t0, 1
sw $t0, 444($sp)
j label_14
label_15:
li $t0, 0
sw $t0, 444($sp)
label_18:
lw $t0, 444($sp)
sub $t0, $t0, $a3
bgez $t0, label_19
lw $t2, 444($sp)
sll $t2, $t2, 2
add $t2, $t2, 448
add $t2, $t2, $sp
lw $t0, ($t2)
add $t4, $0, $t0
la $a0, string_10
li $v0, 4
syscall
lw $t2, 444($sp)
sll $t2, $t2, 2
add $t2, $t2, 448
add $t2, $t2, $sp
lw $a0, ($t2)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
lw $t0, 444($sp)
add $t0, $t0, 1
sw $t0, 444($sp)
j label_18
label_19:
la $a0, string_11
li $v0, 4
syscall
li, $a0, '\n'
li $v0, 11
syscall
la $a0, string_12
li $v0, 4
syscall
li, $a0, '\n'
li $v0, 11
syscall
li $s3, 0
li $s2, 1
li $s4, 2
label_20:
li $t1, 128
sub $t0, $s4, $t1
bgtz $t0, label_21
la $t1, 2
div $s4, $t1
mflo $s1
li $t0, 2
sw $t0, 444($sp)
label_22:
lw $t0, 444($sp)
sub $t0, $t0, $s1
bgtz $t0, label_23
lw $t1, 444($sp)
div $s4, $t1
mflo $t9
lw $t1, 444($sp)
mult $t9, $t1
mflo $t8
move $t7, $s4
lw $t6, 444($sp)
div $t7, $t6
mflo $t5
mult $t5, $t6
mflo $t4
sub $t7, $t7, $t4
move $s0, $t7
j _mod_5
_mod_5:
move $t4, $s0
bnez $t4, label_24
li $s2, 0
label_24:
lw $t0, 444($sp)
add $t0, $t0, 1
sw $t0, 444($sp)
j label_22
label_23:
li $t1, 1
sub $t0, $s2, $t1
bnez $t0,label_28
la $a0, string_13
li $v0, 4
syscall
move $a0, $s4
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
add $s3, $s3, 1
la $t1, 10
div $s3, $t1
mflo $t4
la $t1, 10
mult $t4, $t1
mflo $t8
sub $t0, $t8, $s3
bnez $t0,label_28
la $a0, string_14
li $v0, 4
syscall
li, $a0, '\n'
li $v0, 11
syscall
label_28:
li $s2, 1
add $s4, $s4, 1
j label_20
label_21:
la $a0, string_15
li $v0, 4
syscall
move $a0, $s3
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
lw $ra, 960($sp)
add $sp, $sp, 964
jr $ra
main:
sub $sp, $sp, 984
sw $ra, 980($sp)
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
li, $a0, '\n'
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
li, $a0, '\n'
li $v0, 11
syscall
la $a0, string_1
li $v0, 4
syscall
move $a0, $t5
li $v0, 1
syscall
li, $a0, '\n'
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
li, $a0, '\n'
li $v0, 11
syscall
la $a0, string_3
li $v0, 4
syscall
move $a0, $t5
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
j _swap_6
_swap_6:
li $t0, 2
sw $t0, 440($sp)
_complete_flower_num_0_label_2:
lw $t0, 440($sp)
li $t1, 128
sub $t0, $t0, $t1
bgez $t0, _complete_flower_num_0_label_3
li $t0, -1
sw $t0, 436($sp)
lw $s1, 440($sp)
li $t0, 1
sw $t0, 444($sp)
_complete_flower_num_0_label_4:
lw $t0, 444($sp)
lw $t1, 440($sp)
sub $t0, $t0, $t1
bgez $t0, _complete_flower_num_0_label_5
lw $t0, 440($sp)
lw $t1, 444($sp)
div $t0, $t1
mflo $t9
lw $t1, 444($sp)
mult $t9, $t1
mflo $t8
lw $t7, 440($sp)
lw $t6, 444($sp)
div $t7, $t6
mflo $t5
mult $t5, $t6
mflo $t4
sub $t7, $t7, $t4
move $s0, $t7
j _complete_flower_num_0__mod_0
_complete_flower_num_0__mod_0:
move $t4, $s0
bnez $t4, _complete_flower_num_0_label_9
lw $t0, 436($sp)
add $t0, $t0, 1
sw $t0, 436($sp)
lw $t1, 444($sp)
sub $s1, $s1, $t1
lw $t0, 436($sp)
li $t1, 128
sub $t0, $t0, $t1
bltz $t0, _complete_flower_num_0_label_8
la $a0, string_4
li $v0, 4
syscall
li, $a0, '\n'
li $v0, 11
syscall
j _complete_flower_num_0_label_9
_complete_flower_num_0_label_8:
lw $t0, 444($sp)
lw $t2, 436($sp)
sll $t2, $t2, 2
add $t2, $t2, 448
add $t2, $t2, $sp
sw $t0, ($t2)
_complete_flower_num_0_label_9:
lw $t0, 444($sp)
add $t0, $t0, 1
sw $t0, 444($sp)
j _complete_flower_num_0_label_4
_complete_flower_num_0_label_5:
bnez $s1, _complete_flower_num_0_label_10
la $a0, string_5
li $v0, 4
syscall
lw $a0, 440($sp)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
li $t0, 0
sw $t0, 444($sp)
_complete_flower_num_0_label_12:
lw $t0, 444($sp)
lw $t1, 436($sp)
sub $t0, $t0, $t1
bgtz $t0, _complete_flower_num_0_label_13
lw $t2, 444($sp)
sll $t2, $t2, 2
add $t2, $t2, 448
add $t2, $t2, $sp
lw $t0, ($t2)
add $t4, $0, $t0
la $a0, string_6
li $v0, 4
syscall
lw $t2, 444($sp)
sll $t2, $t2, 2
add $t2, $t2, 448
add $t2, $t2, $sp
lw $a0, ($t2)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
lw $t0, 444($sp)
add $t0, $t0, 1
sw $t0, 444($sp)
j _complete_flower_num_0_label_12
_complete_flower_num_0_label_13:
la $a0, string_7
li $v0, 4
syscall
li, $a0, '\n'
li $v0, 11
syscall
_complete_flower_num_0_label_10:
lw $t0, 440($sp)
add $t0, $t0, 1
sw $t0, 440($sp)
j _complete_flower_num_0_label_2
_complete_flower_num_0_label_3:
la $a0, string_8
li $v0, 4
syscall
li, $a0, '\n'
li $v0, 11
syscall
la $a0, string_9
li $v0, 4
syscall
li, $a0, '\n'
li $v0, 11
syscall
li $a3, 0
li $t0, 100
sw $t0, 444($sp)
_complete_flower_num_0_label_14:
lw $t0, 444($sp)
li $t1, 228
sub $t0, $t0, $t1
bgez $t0, _complete_flower_num_0_label_15
lw $t0, 444($sp)
la $t1, 100
div $t0, $t1
mflo $t0
sw $t0, 436($sp)
lw $t0, 444($sp)
la $t1, 10
div $t0, $t1
mflo $t8
move $t7, $t8
li $t6, 10
div $t7, $t6
mflo $t5
mult $t5, $t6
mflo $t4
sub $t7, $t7, $t4
move $t9, $t7
j _complete_flower_num_0__mod_1
_complete_flower_num_0__mod_1:
sw $t9, 440($sp)
lw $t7, 444($sp)
li $t6, 10
div $t7, $t6
mflo $t5
mult $t5, $t6
mflo $t4
sub $t7, $t7, $t4
move $s1, $t7
j _complete_flower_num_0__mod_2
_complete_flower_num_0__mod_2:
move $s7, $s1
lw $s0, 436($sp)
lw $t9, 440($sp)
move $t8, $s7
la $t1, 100
mult $s0, $t1
mflo $t7
la $t1, 10
mult $t9, $t1
mflo $t6
add $t5, $t7, $t6
add $t4, $t5, $t8
move $a2, $t4
j _complete_flower_num_0__full_num_3
_complete_flower_num_0__full_num_3:
move $s5, $a2
lw $s4, 436($sp)
lw $s3, 440($sp)
move $s2, $s7
mult $s4, $s4
mflo $s1
mult $s1, $s4
mflo $s0
mult $s3, $s3
mflo $t9
mult $t9, $s3
mflo $t8
add $t7, $s0, $t8
mult $s2, $s2
mflo $t6
mult $t6, $s2
mflo $t5
add $t4, $t7, $t5
move $s6, $t4
j _complete_flower_num_0__flower_num_4
_complete_flower_num_0__flower_num_4:
move $t4, $s6
sub $t0, $s5, $t4
bnez $t0,_complete_flower_num_0_label_16
lw $t0, 444($sp)
lw $t2, 424($sp)
sll $t2, $t2, 2
add $t2, $t2, 448
add $t2, $t2, $sp
sw $t0, ($t2)
add $a3, $a3, 1
_complete_flower_num_0_label_16:
lw $t0, 444($sp)
add $t0, $t0, 1
sw $t0, 444($sp)
j _complete_flower_num_0_label_14
_complete_flower_num_0_label_15:
li $t0, 0
sw $t0, 444($sp)
_complete_flower_num_0_label_18:
lw $t0, 444($sp)
sub $t0, $t0, $a3
bgez $t0, _complete_flower_num_0_label_19
lw $t2, 444($sp)
sll $t2, $t2, 2
add $t2, $t2, 448
add $t2, $t2, $sp
lw $t0, ($t2)
add $t4, $0, $t0
la $a0, string_10
li $v0, 4
syscall
lw $t2, 444($sp)
sll $t2, $t2, 2
add $t2, $t2, 448
add $t2, $t2, $sp
lw $a0, ($t2)
li $v0, 1
syscall
li, $a0, '\n'
li $v0, 11
syscall
lw $t0, 444($sp)
add $t0, $t0, 1
sw $t0, 444($sp)
j _complete_flower_num_0_label_18
_complete_flower_num_0_label_19:
la $a0, string_11
li $v0, 4
syscall
li, $a0, '\n'
li $v0, 11
syscall
la $a0, string_12
li $v0, 4
syscall
li, $a0, '\n'
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
sw $t0, 444($sp)
_complete_flower_num_0_label_22:
lw $t0, 444($sp)
sub $t0, $t0, $s1
bgtz $t0, _complete_flower_num_0_label_23
lw $t1, 444($sp)
div $s4, $t1
mflo $t9
lw $t1, 444($sp)
mult $t9, $t1
mflo $t8
move $t7, $s4
lw $t6, 444($sp)
div $t7, $t6
mflo $t5
mult $t5, $t6
mflo $t4
sub $t7, $t7, $t4
move $s0, $t7
j _complete_flower_num_0__mod_5
_complete_flower_num_0__mod_5:
move $t4, $s0
bnez $t4, _complete_flower_num_0_label_24
li $s2, 0
_complete_flower_num_0_label_24:
lw $t0, 444($sp)
add $t0, $t0, 1
sw $t0, 444($sp)
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
li, $a0, '\n'
li $v0, 11
syscall
add $s3, $s3, 1
la $t1, 10
div $s3, $t1
mflo $t4
la $t1, 10
mult $t4, $t1
mflo $t8
sub $t0, $t8, $s3
bnez $t0,_complete_flower_num_0_label_28
la $a0, string_14
li $v0, 4
syscall
li, $a0, '\n'
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
li, $a0, '\n'
li $v0, 11
syscall
j _complete_flower_num_0
_complete_flower_num_0:
li $v0, 10
syscall
