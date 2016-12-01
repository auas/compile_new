.data
$str0: .asciiz "right with test_exp\n"
$str1: .asciiz "wrong with test_exp\n"
$str2: .asciiz "finish test_exp\n"
.text
	li $s7,0x10040000
	move $fp,$sp
	jal main
	j end
const_lab:
	 j main_start
test_exp:
	sw $sp,-4($sp)
	sw $ra,0($sp)
	addi $sp,$sp,-56
	li $t0,1
	sw $t0,4($sp)
	li $t0,3
	sw $t0,8($sp)
	li $t0,5
	sw $t0,12($sp)
	li $t0,6
	sw $t0,16($sp)
	lw $t0,16($sp)
	lw $t1,12($sp)
	add $t0,$t0,$t1
	sw $t0,12($sp)
	lw $t0,12($sp)
	lw $t1,8($sp)
	mult $t0,$t1
	mflo $t0
	sw $t0,8($sp)
	lw $t0,8($sp)
	lw $t1,4($sp)
	add $t0,$t0,$t1
	sw $t0,4($sp)
	lw $t0,4($sp)
	sw $t0,44($sp)
	lw $t0,44($sp)
	sw $t0,20($sp)
	li $t0,3
	sw $t0,24($sp)
	lw $t0,24($sp)
	lw $t1,20($sp)
	mult $t0,$t1
	mflo $t0
	sw $t0,20($sp)
	lw $t0,44($sp)
	sw $t0,28($sp)
	lw $t0,28($sp)
	lw $t1,20($sp)
	add $t0,$t0,$t1
	sw $t0,20($sp)
	lw $t0,0($sp)
	sw $t0,40($sp)
	lw $t0,40($sp)
	sw $t0,32($sp)
	li $t0,1
	sw $t0,36($sp)
	lw $t0,36($sp)
	lw $t1,32($sp)
	add $t0,$t0,$t1
	sw $t0,32($sp)
	lw $v1,32($sp)
	lw $sp,52($sp)
	jr $ra
main:
	sw $sp,-4($sp)
	sw $ra,0($sp)
	addi $sp,$sp,-52
	 j const_lab
main_start:
	li $t0,1
	sw $t0,4($sp)
	li $t0,2
	sw $t0,8($sp)
	li $t0,3
	sw $t0,12($sp)
	lw $t0,12($sp)
	lw $t1,8($sp)
	mult $t0,$t1
	mflo $t0
	sw $t0,8($sp)
	lw $t0,8($sp)
	lw $t1,4($sp)
	add $t0,$t0,$t1
	sw $t0,4($sp)
	lw $t0,4($sp)
	sw $t0,36($sp)
	jal test_exp
	sw $v1,16($sp)
	lw $t0,16($sp)
	sw $t0,32($sp)
	lw $t0,32($sp)
	sw $t0,20($sp)
	lw $a0,20($sp)
	li $v0,1
	syscall
	lw $t0,32($sp)
	sw $t0,24($sp)
	li $t0,136
	sw $t0,28($sp)
	lw $t0,24($sp)
	lw $t1,28($sp)
	beq $t0,$t1,$label0
	nop
	 j $label1
$label0:
	li $v0,4
	la $a0,$str0
	syscall
$label1:
	li $v0,4
	la $a0,$str1
	syscall
	li $v0,4
	la $a0,$str2
	syscall
end: