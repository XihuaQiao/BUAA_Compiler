.data
__change__line__:.asciiz"\n"
__string1_var324:.asciiz"testnum[2] = "
__string1_var337:.asciiz"testnum[1] = "
__string1_var348:.asciiz"testnum[3] = "
__string1_var366:.asciiz"testnum[0] = "
.text
move $s7,$sp
sub $sp,$sp,80
j __program__begin__
abs:
li $s1,0
move $s0,$s1
sw $s0,-12($sp)
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-8($sp)
lw $t9,-8($sp)
li $t8,4
multu $t9,$t8
mflo $t9
li $s1,0
move $s0,$s1
sw $s0,-28($sp)
lw $s1,-28($sp)
move $s0,$s1
sw $s0,-24($sp)
lw $t9,-24($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,0
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-20($sp)
lw $s1,-20($sp)
move $s0,$s1
sw $s0,-16($sp)
li $s1,1
move $s0,$s1
sw $s0,-32($sp)
lw $s3,-16($sp)
lw $s4,-32($sp)
add $s0,$s3,$s4
sw $s0,-16($sp)
lw $s1,-16($sp)
move $s0,$s1
#lw1_array
li $t8,0
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
sw $s0,0($s7)
addu $s7,$s7,$s6
#lw2_array
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-40($sp)
lw $s1,-40($sp)
move $s0,$s1
sw $s0,-36($sp)
li $s1,0
move $s0,$s1
sw $s0,-48($sp)
lw $s1,-48($sp)
move $s0,$s1
sw $s0,-44($sp)
lw $s1,-36($sp)
lw $s2,-44($sp)
slt $s0,$s1,$s2
sw $s0,-52($sp)
lw $s0,-52($sp)
beq $s0,$0,IF11
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-60($sp)
li $s3,0
lw $s4,-60($sp)
sub $s0,$s3,$s4
sw $s0,-56($sp)
li $s1,0
move $s0,$s1
sw $s0,-64($sp)
lw $s3,-56($sp)
lw $s4,-64($sp)
add $s0,$s3,$s4
sw $s0,-56($sp)
lw $v0,-56($sp)
j abs__end__zsjnb__
j IF12
IF11:
IF12:
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-72($sp)
lw $s1,-72($sp)
move $s0,$s1
sw $s0,-68($sp)
li $s1,0
move $s0,$s1
sw $s0,-76($sp)
lw $s3,-68($sp)
lw $s4,-76($sp)
add $s0,$s3,$s4
sw $s0,-68($sp)
lw $v0,-68($sp)
j abs__end__zsjnb__
abs__end__zsjnb__:
jr $31
init:
li $s1,0
move $s0,$s1
sw $s0,-12($sp)
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-8($sp)
lw $s1,-8($sp)
move $s0,$s1
sw $s0,-4($sp)
LOOP52:
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-20($sp)
lw $s1,-20($sp)
move $s0,$s1
sw $s0,-16($sp)
li $s1,10
move $s0,$s1
sw $s0,-28($sp)
lw $s1,-28($sp)
move $s0,$s1
sw $s0,-24($sp)
lw $s1,-16($sp)
lw $s2,-24($sp)
slt $s0,$s1,$s2
sw $s0,-32($sp)
lw $s0,-32($sp)
beq $s0,$0,LOOP53
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-40($sp)
lw $s1,-40($sp)
move $s0,$s1
sw $s0,-36($sp)
lw $t9,-36($sp)
li $t8,4
multu $t9,$t8
mflo $t9
li $s1,0
move $s0,$s1
sw $s0,-48($sp)
lw $s1,-48($sp)
move $s0,$s1
sw $s0,-44($sp)
lw $s1,-44($sp)
move $s0,$s1
#lw1_array
li $t8,0
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
sw $s0,0($s7)
addu $s7,$s7,$s6
#lw2_array
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-56($sp)
lw $s1,-56($sp)
move $s0,$s1
sw $s0,-52($sp)
li $s1,1
move $s0,$s1
sw $s0,-60($sp)
lw $s3,-52($sp)
lw $s4,-60($sp)
add $s0,$s3,$s4
sw $s0,-52($sp)
lw $s1,-52($sp)
move $s0,$s1
sw $s0,-4($sp)
j LOOP52
LOOP53:
li $s1,1
move $s0,$s1
sw $s0,-68($sp)
lw $s1,-68($sp)
move $s0,$s1
sw $s0,-64($sp)
lw $t9,-64($sp)
li $t8,4
multu $t9,$t8
mflo $t9
li $s1,1
move $s0,$s1
sw $s0,-84($sp)
lw $s1,-84($sp)
move $s0,$s1
sw $s0,-80($sp)
lw $t9,-80($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,0
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-76($sp)
lw $s1,-76($sp)
move $s0,$s1
sw $s0,-72($sp)
li $s1,1
move $s0,$s1
sw $s0,-88($sp)
lw $s3,-72($sp)
lw $s4,-88($sp)
add $s0,$s3,$s4
sw $s0,-72($sp)
lw $s1,-72($sp)
move $s0,$s1
#lw1_array
li $t8,0
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
sw $s0,0($s7)
addu $s7,$s7,$s6
#lw2_array
init__end__zsjnb__:
jr $31
show:
li $s1,3
move $s0,$s1
sw $s0,-12($sp)
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-8($sp)
lw $t9,-8($sp)
li $t8,4
multu $t9,$t8
mflo $t9
li $s1,1
move $s0,$s1
sw $s0,-20($sp)
lw $s1,-20($sp)
move $s0,$s1
sw $s0,-16($sp)
lw $s1,-16($sp)
move $s0,$s1
#lw1_array
li $t8,0
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
sw $s0,0($s7)
addu $s7,$s7,$s6
#lw2_array
li $s1,0
move $s0,$s1
sw $s0,-28($sp)
lw $s1,-28($sp)
move $s0,$s1
sw $s0,-24($sp)
lw $s1,-24($sp)
move $s0,$s1
sw $s0,-4($sp)
LOOP113:
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-36($sp)
lw $s1,-36($sp)
move $s0,$s1
sw $s0,-32($sp)
li $s1,4
move $s0,$s1
sw $s0,-44($sp)
lw $s1,-44($sp)
move $s0,$s1
sw $s0,-40($sp)
lw $s1,-32($sp)
lw $s2,-40($sp)
slt $s0,$s1,$s2
sw $s0,-48($sp)
lw $s0,-48($sp)
beq $s0,$0,LOOP114
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-64($sp)
lw $s1,-64($sp)
move $s0,$s1
sw $s0,-60($sp)
lw $t9,-60($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,0
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-56($sp)
lw $s1,-56($sp)
move $s0,$s1
sw $s0,-52($sp)
lw $s0,-52($sp)
move $a0,$s0
li $v0,1
syscall
la $a0, __change__line__
li $v0, 4
syscall
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-72($sp)
lw $s1,-72($sp)
move $s0,$s1
sw $s0,-68($sp)
li $s1,1
move $s0,$s1
sw $s0,-76($sp)
lw $s3,-68($sp)
lw $s4,-76($sp)
add $s0,$s3,$s4
sw $s0,-68($sp)
lw $s1,-68($sp)
move $s0,$s1
sw $s0,-4($sp)
j LOOP113
LOOP114:
show__end__zsjnb__:
jr $31
times:
li $s1,2
move $s0,$s1
sw $s0,-16($sp)
lw $s1,-16($sp)
move $s0,$s1
sw $s0,-12($sp)
lw $t9,-12($sp)
li $t8,4
multu $t9,$t8
mflo $t9
li $s1,1
move $s0,$s1
sw $s0,-24($sp)
lw $s1,-24($sp)
move $s0,$s1
sw $s0,-20($sp)
lw $s1,-20($sp)
move $s0,$s1
#lw1_array
li $t8,0
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
sw $s0,0($s7)
addu $s7,$s7,$s6
#lw2_array
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-32($sp)
lw $s3,-32($sp)
lw $s4,-8($sp)
mult $s3,$s4
mflo $s0
sw $s0,-32($sp)
lw $s1,-32($sp)
move $s0,$s1
sw $s0,-28($sp)
lw $v0,-28($sp)
j times__end__zsjnb__
times__end__zsjnb__:
jr $31
sum4:
li $s1,3
move $s0,$s1
sw $s0,-24($sp)
lw $s1,-24($sp)
move $s0,$s1
sw $s0,-20($sp)
lw $t9,-20($sp)
li $t8,4
multu $t9,$t8
mflo $t9
li $s1,1
move $s0,$s1
sw $s0,-32($sp)
lw $s1,-32($sp)
move $s0,$s1
sw $s0,-28($sp)
li $s1,3
move $s0,$s1
sw $s0,-44($sp)
lw $s1,-44($sp)
move $s0,$s1
sw $s0,-40($sp)
lw $t9,-40($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,0
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-36($sp)
lw $s3,-28($sp)
lw $s4,-36($sp)
add $s0,$s3,$s4
sw $s0,-28($sp)
lw $s1,-28($sp)
move $s0,$s1
#lw1_array
li $t8,0
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
sw $s0,0($s7)
addu $s7,$s7,$s6
#lw2_array
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-52($sp)
lw $s1,-52($sp)
move $s0,$s1
sw $s0,-48($sp)
lw $s1,-8($sp)
move $s0,$s1
sw $s0,-56($sp)
lw $s3,-48($sp)
lw $s4,-56($sp)
add $s0,$s3,$s4
sw $s0,-48($sp)
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-60($sp)
lw $s3,-48($sp)
lw $s4,-60($sp)
add $s0,$s3,$s4
sw $s0,-48($sp)
lw $s1,-16($sp)
move $s0,$s1
sw $s0,-64($sp)
lw $s3,-48($sp)
lw $s4,-64($sp)
add $s0,$s3,$s4
sw $s0,-48($sp)
lw $v0,-48($sp)
j sum4__end__zsjnb__
sum4__end__zsjnb__:
jr $31
fi:
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-12($sp)
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-8($sp)
lw $s0,-8($sp)
beq $s0,$0,IF190
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-20($sp)
lw $s1,-20($sp)
move $s0,$s1
sw $s0,-16($sp)
lw $t9,-16($sp)
li $t8,4
multu $t9,$t8
mflo $t9
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-36($sp)
lw $s1,-36($sp)
move $s0,$s1
sw $s0,-32($sp)
li $s1,1
move $s0,$s1
sw $s0,-40($sp)
lw $s3,-32($sp)
lw $s4,-40($sp)
add $s0,$s3,$s4
sw $s0,-32($sp)
lw $t9,-32($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-28($sp)
lw $s1,-28($sp)
move $s0,$s1
sw $s0,-24($sp)
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-52($sp)
lw $s1,-52($sp)
move $s0,$s1
sw $s0,-48($sp)
li $s1,-2
move $s0,$s1
sw $s0,-56($sp)
lw $s3,-48($sp)
lw $s4,-56($sp)
sub $s0,$s3,$s4
sw $s0,-48($sp)
lw $t9,-48($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-44($sp)
lw $s3,-24($sp)
lw $s4,-44($sp)
add $s0,$s3,$s4
sw $s0,-24($sp)
lw $s1,-24($sp)
move $s0,$s1
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
sw $s0,0($s7)
addu $s7,$s7,$s6
#lw2_array
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-64($sp)
lw $s1,-64($sp)
move $s0,$s1
sw $s0,-60($sp)
li $s1,1
move $s0,$s1
sw $s0,-68($sp)
lw $s3,-60($sp)
lw $s4,-68($sp)
sub $s0,$s3,$s4
sw $s0,-60($sp)
sw $31,-0($sp)
lw $s0,-60($sp)
sw $s0,-120($sp)
sub $sp,$sp,116
jal fi
add $sp,$sp,116
lw $31,-0($sp)
j IF191
IF190:
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-76($sp)
lw $s1,-76($sp)
move $s0,$s1
sw $s0,-72($sp)
lw $t9,-72($sp)
li $t8,4
multu $t9,$t8
mflo $t9
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-92($sp)
lw $s1,-92($sp)
move $s0,$s1
sw $s0,-88($sp)
li $s1,1
move $s0,$s1
sw $s0,-96($sp)
lw $s3,-88($sp)
lw $s4,-96($sp)
add $s0,$s3,$s4
sw $s0,-88($sp)
lw $t9,-88($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-84($sp)
lw $s1,-84($sp)
move $s0,$s1
sw $s0,-80($sp)
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-108($sp)
lw $s1,-108($sp)
move $s0,$s1
sw $s0,-104($sp)
li $s1,-2
move $s0,$s1
sw $s0,-112($sp)
lw $s3,-104($sp)
lw $s4,-112($sp)
sub $s0,$s3,$s4
sw $s0,-104($sp)
lw $t9,-104($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-100($sp)
lw $s3,-80($sp)
lw $s4,-100($sp)
add $s0,$s3,$s4
sw $s0,-80($sp)
lw $s1,-80($sp)
move $s0,$s1
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
sw $s0,0($s7)
addu $s7,$s7,$s6
#lw2_array
j fi__end__zsjnb__
IF191:
fi__end__zsjnb__:
jr $31
main:
li $v0, 12
syscall
move $s0, $v0
sw $s0,-16($sp)
li $v0, 5
syscall
move $s0, $v0
sw $s0,-4($sp)
sw $31,-0($sp)
sub $sp,$sp,540
jal init
add $sp,$sp,540
lw $31,-0($sp)
li $s1,2
move $s0,$s1
sw $s0,-48($sp)
lw $s1,-48($sp)
move $s0,$s1
sw $s0,-44($sp)
li $s1,2
move $s0,$s1
sw $s0,-56($sp)
li $s3,0
lw $s4,-56($sp)
sub $s0,$s3,$s4
sw $s0,-52($sp)
sw $31,-0($sp)
lw $s0,-44($sp)
sw $s0,-544($sp)
lw $s0,-52($sp)
sw $s0,-548($sp)
sub $sp,$sp,540
jal times
add $sp,$sp,540
lw $31,-0($sp)
sw $v0,-60($sp)
lw $s1,-60($sp)
move $s0,$s1
sw $s0,-40($sp)
lw $s1,-40($sp)
move $s0,$s1
sw $s0,-36($sp)
sw $31,-0($sp)
lw $s0,-36($sp)
sw $s0,-544($sp)
sub $sp,$sp,540
jal abs
add $sp,$sp,540
lw $31,-0($sp)
sw $v0,-64($sp)
lw $s1,-64($sp)
move $s0,$s1
sw $s0,-32($sp)
lw $s1,-32($sp)
move $s0,$s1
sw $s0,-28($sp)
li $s1,1
move $s0,$s1
sw $s0,-80($sp)
li $s3,0
lw $s4,-80($sp)
sub $s0,$s3,$s4
sw $s0,-76($sp)
sw $31,-0($sp)
lw $s0,-76($sp)
sw $s0,-544($sp)
sub $sp,$sp,540
jal abs
add $sp,$sp,540
lw $31,-0($sp)
sw $v0,-84($sp)
lw $s1,-84($sp)
move $s0,$s1
sw $s0,-72($sp)
lw $s1,-72($sp)
move $s0,$s1
sw $s0,-68($sp)
li $s1,3
move $s0,$s1
sw $s0,-100($sp)
li $s3,0
lw $s4,-100($sp)
sub $s0,$s3,$s4
sw $s0,-96($sp)
sw $31,-0($sp)
lw $s0,-96($sp)
sw $s0,-544($sp)
sub $sp,$sp,540
jal abs
add $sp,$sp,540
lw $31,-0($sp)
sw $v0,-104($sp)
lw $s1,-104($sp)
move $s0,$s1
sw $s0,-92($sp)
lw $s1,-92($sp)
move $s0,$s1
sw $s0,-88($sp)
li $s1,22
move $s0,$s1
sw $s0,-120($sp)
lw $s1,-120($sp)
move $s0,$s1
sw $s0,-116($sp)
sw $31,-0($sp)
lw $s0,-116($sp)
sw $s0,-544($sp)
sub $sp,$sp,540
jal abs
add $sp,$sp,540
lw $31,-0($sp)
sw $v0,-124($sp)
lw $s1,-124($sp)
move $s0,$s1
sw $s0,-112($sp)
lw $s1,-112($sp)
move $s0,$s1
sw $s0,-108($sp)
sw $31,-0($sp)
lw $s0,-28($sp)
sw $s0,-544($sp)
lw $s0,-68($sp)
sw $s0,-548($sp)
lw $s0,-88($sp)
sw $s0,-552($sp)
lw $s0,-108($sp)
sw $s0,-556($sp)
sub $sp,$sp,540
jal sum4
add $sp,$sp,540
lw $31,-0($sp)
sw $v0,-128($sp)
lw $s1,-128($sp)
move $s0,$s1
sw $s0,-24($sp)
lw $s1,-24($sp)
move $s0,$s1
sw $s0,-20($sp)
lw $s0,-20($sp)
move $a0,$s0
li $v0,1
syscall
la $a0, __change__line__
li $v0, 4
syscall
li $s1,9
move $s0,$s1
sw $s0,-136($sp)
lw $s1,-136($sp)
move $s0,$s1
sw $s0,-132($sp)
lw $t9,-132($sp)
li $t8,4
multu $t9,$t8
mflo $t9
li $s1,1
move $s0,$s1
sw $s0,-144($sp)
lw $s1,-144($sp)
move $s0,$s1
sw $s0,-140($sp)
lw $s1,-140($sp)
move $s0,$s1
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
sw $s0,0($s7)
addu $s7,$s7,$s6
#lw2_array
li $s1,7
move $s0,$s1
sw $s0,-152($sp)
lw $s1,-152($sp)
move $s0,$s1
sw $s0,-148($sp)
li $s1,'b'
move $s0,$s1
sw $s0,-156($sp)
lw $s3,-148($sp)
lw $s4,-156($sp)
add $s0,$s3,$s4
sw $s0,-148($sp)
li $s1,'a'
move $s0,$s1
sw $s0,-160($sp)
lw $s3,-148($sp)
lw $s4,-160($sp)
sub $s0,$s3,$s4
sw $s0,-148($sp)
lw $t9,-148($sp)
li $t8,4
multu $t9,$t8
mflo $t9
li $s1,2
move $s0,$s1
sw $s0,-168($sp)
lw $s1,-168($sp)
move $s0,$s1
sw $s0,-164($sp)
lw $s1,-164($sp)
move $s0,$s1
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
sw $s0,0($s7)
addu $s7,$s7,$s6
#lw2_array
li $s1,7
move $s0,$s1
sw $s0,-176($sp)
lw $s1,-176($sp)
move $s0,$s1
sw $s0,-172($sp)
sw $31,-0($sp)
lw $s0,-172($sp)
sw $s0,-544($sp)
sub $sp,$sp,540
jal fi
add $sp,$sp,540
lw $31,-0($sp)
la $a0, __string1_var324
li $v0, 4
syscall
li $s1,8
move $s0,$s1
sw $s0,-200($sp)
lw $s1,-200($sp)
move $s0,$s1
sw $s0,-196($sp)
lw $t9,-196($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-192($sp)
lw $s1,-192($sp)
move $s0,$s1
sw $s0,-188($sp)
lw $t9,-188($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-184($sp)
lw $s1,-184($sp)
move $s0,$s1
sw $s0,-180($sp)
lw $s0,-180($sp)
move $a0,$s0
li $v0,1
syscall
la $a0, __change__line__
li $v0, 4
syscall
la $a0, __string1_var337
li $v0, 4
syscall
li $s1,1
move $s0,$s1
sw $s0,-224($sp)
lw $s1,-224($sp)
move $s0,$s1
sw $s0,-220($sp)
lw $t9,-220($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-216($sp)
lw $s1,-216($sp)
move $s0,$s1
sw $s0,-212($sp)
lw $s0,-212($sp)
move $a0,$s0
li $v0,1
syscall
la $a0, __change__line__
li $v0, 4
syscall
la $a0, __string1_var348
li $v0, 4
syscall
li $s1,5
move $s0,$s1
sw $s0,-264($sp)
lw $s1,-264($sp)
move $s0,$s1
sw $s0,-260($sp)
lw $t9,-260($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-256($sp)
lw $s1,-256($sp)
move $s0,$s1
sw $s0,-252($sp)
lw $t9,-252($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-248($sp)
lw $s1,-248($sp)
move $s0,$s1
sw $s0,-244($sp)
li $s1,9
move $s0,$s1
sw $s0,-276($sp)
lw $s1,-276($sp)
move $s0,$s1
sw $s0,-272($sp)
lw $t9,-272($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-268($sp)
lw $s3,-244($sp)
lw $s4,-268($sp)
add $s0,$s3,$s4
sw $s0,-244($sp)
lw $t9,-244($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-240($sp)
lw $s1,-240($sp)
move $s0,$s1
sw $s0,-236($sp)
lw $s0,-236($sp)
move $a0,$s0
li $v0,1
syscall
la $a0, __change__line__
li $v0, 4
syscall
la $a0, __string1_var366
li $v0, 4
syscall
li $s1,0
move $s0,$s1
sw $s0,-300($sp)
lw $s1,-300($sp)
move $s0,$s1
sw $s0,-296($sp)
lw $t9,-296($sp)
li $t8,4
multu $t9,$t8
mflo $t9
#lw1_array
li $t8,40
addu $t8,$t8,$t9
move $s6,$t8
subu $s7,$s7,$s6
lw $s1,0($s7)
addu $s7,$s7,$s6
#lw2_array
move $s0,$s1
sw $s0,-292($sp)
lw $s1,-292($sp)
move $s0,$s1
sw $s0,-288($sp)
lw $s0,-288($sp)
move $a0,$s0
li $v0,1
syscall
la $a0, __change__line__
li $v0, 4
syscall
li $s1,0
move $s0,$s1
sw $s0,-316($sp)
lw $s1,-316($sp)
move $s0,$s1
sw $s0,-312($sp)
lw $s1,-312($sp)
move $s0,$s1
sw $s0,-8($sp)
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-324($sp)
lw $s1,-324($sp)
move $s0,$s1
sw $s0,-320($sp)
li $s1,10
move $s0,$s1
sw $s0,-332($sp)
lw $s1,-332($sp)
move $s0,$s1
sw $s0,-328($sp)
lw $s1,-320($sp)
lw $s2,-328($sp)
slt $s0,$s2,$s1
sw $s0,-336($sp)
lw $s0,-336($sp)
beq $s0,$0,IF379
li $s1,0
move $s0,$s1
sw $s0,-344($sp)
lw $s1,-344($sp)
move $s0,$s1
sw $s0,-340($sp)
lw $s1,-340($sp)
move $s0,$s1
sw $s0,-12($sp)
LOOP398:
lw $s1,-8($sp)
move $s0,$s1
sw $s0,-352($sp)
lw $s1,-352($sp)
move $s0,$s1
sw $s0,-348($sp)
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-356($sp)
lw $s3,-348($sp)
lw $s4,-356($sp)
add $s0,$s3,$s4
sw $s0,-348($sp)
lw $s1,-348($sp)
move $s0,$s1
sw $s0,-8($sp)
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-364($sp)
lw $s1,-364($sp)
move $s0,$s1
sw $s0,-360($sp)
li $s1,1
move $s0,$s1
sw $s0,-368($sp)
lw $s3,-360($sp)
lw $s4,-368($sp)
add $s0,$s3,$s4
sw $s0,-360($sp)
lw $s1,-360($sp)
move $s0,$s1
sw $s0,-12($sp)
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-376($sp)
lw $s1,-376($sp)
move $s0,$s1
sw $s0,-372($sp)
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-384($sp)
lw $s1,-384($sp)
move $s0,$s1
sw $s0,-380($sp)
lw $s1,-372($sp)
lw $s2,-380($sp)
slt $s0,$s1,$s2
sw $s0,-388($sp)
lw $s0,-388($sp)
bne $s0,$0,LOOP398
j IF380
IF379:
lw $s1,-16($sp)
move $s0,$s1
sw $s0,-396($sp)
lw $s1,-396($sp)
move $s0,$s1
sw $s0,-392($sp)
li $s1,0
move $s0,$s1
sw $s0,-400($sp)
lw $s3,-392($sp)
lw $s4,-400($sp)
add $s0,$s3,$s4
sw $s0,-392($sp)
li $s1,'+'
move $s0,$s1
sw $s0,-408($sp)
lw $s1,-408($sp)
move $s0,$s1
sw $s0,-404($sp)
li $s1,0
move $s0,$s1
sw $s0,-412($sp)
lw $s3,-404($sp)
lw $s4,-412($sp)
add $s0,$s3,$s4
sw $s0,-404($sp)
lw $s1,-392($sp)
lw $s2,-404($sp)
slt $s3,$s1,$s2
slt $s4,$s2,$s1
or $s0,$s3,$s4 
li $s1,1
subu $s0,$s1,$s0
sw $s0,-416($sp)
lw $s0,-416($sp)
beq $s0,$0,IF439
li $s1,0
move $s0,$s1
sw $s0,-424($sp)
lw $s1,-424($sp)
move $s0,$s1
sw $s0,-420($sp)
lw $s1,-420($sp)
move $s0,$s1
sw $s0,-12($sp)
LOOP460:
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-432($sp)
lw $s1,-432($sp)
move $s0,$s1
sw $s0,-428($sp)
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-440($sp)
lw $s1,-440($sp)
move $s0,$s1
sw $s0,-436($sp)
li $s1,3
move $s0,$s1
sw $s0,-444($sp)
lw $s3,-436($sp)
lw $s4,-444($sp)
add $s0,$s3,$s4
sw $s0,-436($sp)
lw $s1,-428($sp)
lw $s2,-436($sp)
slt $s0,$s1,$s2
sw $s0,-448($sp)
lw $s0,-448($sp)
beq $s0,$0,LOOP461
lw $s1,-8($sp)
move $s0,$s1
sw $s0,-456($sp)
lw $s1,-456($sp)
move $s0,$s1
sw $s0,-452($sp)
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-460($sp)
lw $s3,-452($sp)
lw $s4,-460($sp)
add $s0,$s3,$s4
sw $s0,-452($sp)
lw $s1,-452($sp)
move $s0,$s1
sw $s0,-8($sp)
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-468($sp)
lw $s1,-468($sp)
move $s0,$s1
sw $s0,-464($sp)
li $s1,3
move $s0,$s1
sw $s0,-472($sp)
lw $s3,-464($sp)
lw $s4,-472($sp)
add $s0,$s3,$s4
sw $s0,-464($sp)
lw $s1,-464($sp)
move $s0,$s1
sw $s0,-12($sp)
j LOOP460
LOOP461:
j IF440
IF439:
li $s1,0
move $s0,$s1
sw $s0,-480($sp)
lw $s1,-480($sp)
move $s0,$s1
sw $s0,-476($sp)
lw $s1,-476($sp)
move $s0,$s1
sw $s0,-12($sp)
LOOP510:
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-488($sp)
lw $s1,-488($sp)
move $s0,$s1
sw $s0,-484($sp)
lw $s1,-4($sp)
move $s0,$s1
sw $s0,-496($sp)
lw $s1,-496($sp)
move $s0,$s1
sw $s0,-492($sp)
li $s1,3
move $s0,$s1
sw $s0,-500($sp)
lw $s3,-492($sp)
lw $s4,-500($sp)
add $s0,$s3,$s4
sw $s0,-492($sp)
lw $s1,-484($sp)
lw $s2,-492($sp)
slt $s0,$s1,$s2
sw $s0,-504($sp)
lw $s0,-504($sp)
beq $s0,$0,LOOP511
lw $s1,-8($sp)
move $s0,$s1
sw $s0,-512($sp)
lw $s1,-512($sp)
move $s0,$s1
sw $s0,-508($sp)
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-516($sp)
lw $s3,-508($sp)
lw $s4,-516($sp)
sub $s0,$s3,$s4
sw $s0,-508($sp)
lw $s1,-508($sp)
move $s0,$s1
sw $s0,-8($sp)
lw $s1,-12($sp)
move $s0,$s1
sw $s0,-524($sp)
lw $s1,-524($sp)
move $s0,$s1
sw $s0,-520($sp)
li $s1,3
move $s0,$s1
sw $s0,-528($sp)
lw $s3,-520($sp)
lw $s4,-528($sp)
add $s0,$s3,$s4
sw $s0,-520($sp)
lw $s1,-520($sp)
move $s0,$s1
sw $s0,-12($sp)
j LOOP510
LOOP511:
IF440:
IF380:
sw $31,-0($sp)
sub $sp,$sp,540
jal show
add $sp,$sp,540
lw $31,-0($sp)
lw $s1,-8($sp)
move $s0,$s1
sw $s0,-536($sp)
lw $s1,-536($sp)
move $s0,$s1
sw $s0,-532($sp)
lw $s0,-532($sp)
move $a0,$s0
li $v0,1
syscall
la $a0, __change__line__
li $v0, 4
syscall
j main__end__zsjnb__
main__end__zsjnb__:
jr $31
__program__begin__:
jal main
__program_end__:
