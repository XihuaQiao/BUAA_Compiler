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
lw $t4, 20($sp)
li $t1, 1
sub $t0, $t4, $t1
bgtz $t0, label_0
li $v0, 1
lw $ra, 24($sp)
add $sp, $sp, 28
jr $ra
label_0:
sub $t0, $t4, 1
sw $t0, 8($sp)
jal factorial
mult $t4, $v0
mflo $t0
sw $t0, 4($sp)
lw $v0, 4($sp)
lw $ra, 24($sp)
add $sp, $sp, 28
jr $ra
main:
sub $sp, $sp, 992
sw $ra, 988($sp)
jal int
move $t0, $v0
sw $t0, 984($sp)
la $a0, string_16
li $v0, 4
syscall
lw $a0, 984($sp)
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
li $t0, 5
sw $t0, 972($sp)
li $t0, 10
sw $t0, 968($sp)
la $a0, string_0
li $v0, 4
syscall
lw $a0, 972($sp)
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
la $a0, string_1
li $v0, 4
syscall
lw $a0, 968($sp)
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
lw $t0, 972($sp)
sw $t0, 976($sp)
lw $t0, 968($sp)
sw $t0, 972($sp)
lw $t0, 976($sp)
sw $t0, 968($sp)
la $a0, string_2
li $v0, 4
syscall
lw $a0, 972($sp)
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
la $a0, string_3
li $v0, 4
syscall
lw $a0, 968($sp)
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
j _swap_6
_swap_6:
li $t0, 2
sw $t0, 448($sp)
_complete_flower_num_0_label_2:
lw $t0, 448($sp)
li $t1, 128
sub $t0, $t0, $t1
bgez $t0, _complete_flower_num_0_label_3
li $t0, -1
sw $t0, 444($sp)
lw $t0, 448($sp)
sw $t0, 440($sp)
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
mflo $t0
sw $t0, 384($sp)
lw $t0, 384($sp)
lw $t1, 452($sp)
mult $t0, $t1
mflo $t0
sw $t0, 436($sp)
lw $t0, 448($sp)
sw $t0, 180($sp)
lw $t0, 452($sp)
sw $t0, 176($sp)
lw $t0, 180($sp)
lw $t1, 176($sp)
div $t0, $t1
mflo $t0
sw $t0, 192($sp)
lw $t0, 192($sp)
lw $t1, 176($sp)
mult $t0, $t1
mflo $t0
sw $t0, 188($sp)
lw $t0, 180($sp)
lw $t1, 188($sp)
sub $t0, $t0, $t1
sw $t0, 180($sp)
lw $t0, 180($sp)
sw $t0, 172($sp)
j _complete_flower_num_0__mod_0
_complete_flower_num_0__mod_0:
lw $t0, 172($sp)
sw $t0, 368($sp)
lw $t0, 368($sp)
bnez $t0, _complete_flower_num_0_label_9
lw $t0, 444($sp)
add $t0, $t0, 1
sw $t0, 444($sp)
lw $t0, 440($sp)
lw $t1, 452($sp)
sub $t0, $t0, $t1
sw $t0, 440($sp)
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
lw $t0, 440($sp)
bnez $t0, _complete_flower_num_0_label_10
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
lw $t0, ($t2)
sw $t0, 336($sp)
la $a0, string_6
li $v0, 4
syscall
lw $a0, 336($sp)
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
sw $t0, 144($sp)
j _complete_flower_num_0__mod_1
_complete_flower_num_0__mod_1:
lw $t0, 144($sp)
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
sw $t0, 116($sp)
j _complete_flower_num_0__mod_2
_complete_flower_num_0__mod_2:
lw $t0, 116($sp)
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
mflo $t0
sw $t0, 104($sp)
lw $t0, 112($sp)
lw $t1, 104($sp)
add $t0, $t0, $t1
sw $t0, 100($sp)
lw $t0, 100($sp)
lw $t1, 84($sp)
add $t0, $t0, $t1
sw $t0, 96($sp)
lw $t0, 96($sp)
sw $t0, 80($sp)
j _complete_flower_num_0__full_num_3
_complete_flower_num_0__full_num_3:
lw $t0, 80($sp)
sw $t0, 292($sp)
lw $t0, 444($sp)
sw $t0, 40($sp)
lw $t0, 448($sp)
sw $t0, 36($sp)
lw $t0, 408($sp)
sw $t0, 32($sp)
lw $t0, 40($sp)
lw $t1, 40($sp)
mult $t0, $t1
mflo $t0
sw $t0, 76($sp)
lw $t0, 76($sp)
lw $t1, 40($sp)
mult $t0, $t1
mflo $t0
sw $t0, 72($sp)
lw $t0, 36($sp)
lw $t1, 36($sp)
mult $t0, $t1
mflo $t0
sw $t0, 64($sp)
lw $t0, 64($sp)
lw $t1, 36($sp)
mult $t0, $t1
mflo $t0
sw $t0, 60($sp)
lw $t0, 72($sp)
lw $t1, 60($sp)
add $t0, $t0, $t1
sw $t0, 56($sp)
lw $t0, 32($sp)
lw $t1, 32($sp)
mult $t0, $t1
mflo $t0
sw $t0, 52($sp)
lw $t0, 52($sp)
lw $t1, 32($sp)
mult $t0, $t1
mflo $t0
sw $t0, 48($sp)
lw $t0, 56($sp)
lw $t1, 48($sp)
add $t0, $t0, $t1
sw $t0, 44($sp)
lw $t0, 44($sp)
sw $t0, 28($sp)
j _complete_flower_num_0__flower_num_4
_complete_flower_num_0__flower_num_4:
lw $t0, 28($sp)
sw $t0, 288($sp)
lw $t0, 292($sp)
lw $t1, 288($sp)
sub $t0, $t0, $t1
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
li $t0, 0
sw $t0, 420($sp)
li $t0, 1
sw $t0, 416($sp)
li $t0, 2
sw $t0, 428($sp)
_complete_flower_num_0_label_20:
lw $t0, 428($sp)
li $t1, 128
sub $t0, $t0, $t1
bgtz $t0, _complete_flower_num_0_label_21
lw $t0, 428($sp)
la $t1, 2
div $t0, $t1
mflo $t0
sw $t0, 424($sp)
li $t0, 2
sw $t0, 452($sp)
_complete_flower_num_0_label_22:
lw $t0, 452($sp)
lw $t1, 424($sp)
sub $t0, $t0, $t1
bgtz $t0, _complete_flower_num_0_label_23
lw $t0, 428($sp)
lw $t1, 452($sp)
div $t0, $t1
mflo $t0
sw $t0, 248($sp)
lw $t0, 248($sp)
lw $t1, 452($sp)
mult $t0, $t1
mflo $t0
sw $t0, 412($sp)
lw $t0, 428($sp)
sw $t0, 8($sp)
lw $t0, 452($sp)
sw $t0, 4($sp)
lw $t0, 8($sp)
lw $t1, 4($sp)
div $t0, $t1
mflo $t0
sw $t0, 20($sp)
lw $t0, 20($sp)
lw $t1, 4($sp)
mult $t0, $t1
mflo $t0
sw $t0, 16($sp)
lw $t0, 8($sp)
lw $t1, 16($sp)
sub $t0, $t0, $t1
sw $t0, 8($sp)
lw $t0, 8($sp)
sw $t0, 0($sp)
j _complete_flower_num_0__mod_5
_complete_flower_num_0__mod_5:
lw $t0, 0($sp)
sw $t0, 232($sp)
lw $t0, 232($sp)
bnez $t0, _complete_flower_num_0_label_24
li $t0, 0
sw $t0, 416($sp)
_complete_flower_num_0_label_24:
lw $t0, 452($sp)
add $t0, $t0, 1
sw $t0, 452($sp)
j _complete_flower_num_0_label_22
_complete_flower_num_0_label_23:
lw $t0, 416($sp)
li $t1, 1
sub $t0, $t0, $t1
bnez $t0,_complete_flower_num_0_label_28
la $a0, string_13
li $v0, 4
syscall
lw $a0, 428($sp)
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
lw $t0, 420($sp)
add $t0, $t0, 1
sw $t0, 420($sp)
lw $t0, 420($sp)
la $t1, 10
div $t0, $t1
mflo $t0
sw $t0, 216($sp)
lw $t0, 216($sp)
la $t1, 10
mult $t0, $t1
mflo $t0
sw $t0, 412($sp)
lw $t0, 412($sp)
lw $t1, 420($sp)
sub $t0, $t0, $t1
bnez $t0,_complete_flower_num_0_label_28
la $a0, string_14
li $v0, 4
syscall
li $a0, '\n'
li $v0, 11
syscall
_complete_flower_num_0_label_28:
li $t0, 1
sw $t0, 416($sp)
lw $t0, 428($sp)
add $t0, $t0, 1
sw $t0, 428($sp)
j _complete_flower_num_0_label_20
_complete_flower_num_0_label_21:
la $a0, string_15
li $v0, 4
syscall
lw $a0, 420($sp)
li $v0, 1
syscall
li $a0, '\n'
li $v0, 11
syscall
j _complete_flower_num_0
_complete_flower_num_0:
li $v0, 10
syscall
