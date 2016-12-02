.data
$str0: .asciiz "hello!\n"
$str1: .asciiz "enter an int\n"
$str2: .asciiz "\n you enter: "
$str3: .asciiz "show array result"
$str4: .asciiz "\n*\n"
$str5: .asciiz "right with test_exp\n"
$str6: .asciiz "wrong with test_exp\n"
$str7: .asciiz "finish test_exp\n"
$str8: .asciiz "start testing scanf\n"
$str9: .asciiz "\n start testing func\n"
$str10: .asciiz "end testing func\n"
$str11: .asciiz "start testing cycle\n"
$str12: .asciiz "\nend testing cycle\n"
$str13: .asciiz "start testing array\n"
$str14: .asciiz "\nend testing array\n"
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
	addi $sp,$sp,-72
	li $t0,1
	sw $t0,8($sp)
	li $t0,3
	sw $t0,12($sp)
	li $t0,5
	sw $t0,20($sp)
	li $t0,6
	sw $t0,24($sp)
	lw $t0,20($sp)
	lw $t1,24($sp)
	add $t0,$t0,$t1
	sw $t0,20($sp)
	lw $t0,20($sp)
	lw $t1,12($sp)
	mult $t0,$t1
	mflo $t0
	sw $t0,12($sp)
	lw $t0,8($sp)
	lw $t1,12($sp)
	add $t0,$t0,$t1
	sw $t0,8($sp)
	lw $t0,8($sp)
	sw $t0,60($sp)
	lw $t0,60($sp)
	sw $t0,32($sp)
	li $t0,3
	sw $t0,36($sp)
	lw $t0,36($sp)
	lw $t1,32($sp)
	mult $t0,$t1
	mflo $t0
	sw $t0,32($sp)
	lw $t0,60($sp)
	sw $t0,40($sp)
	lw $t0,32($sp)
	lw $t1,40($sp)
	add $t0,$t0,$t1
	sw $t0,32($sp)
	lw $t0,32($sp)
	sw $t0,56($sp)
	lw $t0,56($sp)
	sw $t0,48($sp)
	li $t0,1
	sw $t0,52($sp)
	lw $t0,48($sp)
	lw $t1,52($sp)
	add $t0,$t0,$t1
	sw $t0,48($sp)
	lw $v1,48($sp)
	lw $ra,72($sp)
	lw $sp,68($sp)
	jr $ra
	lw $ra,72($sp)
	lw $sp,68($sp)
	jr $ra
test_func:
	sw $sp,-4($sp)
	sw $ra,0($sp)
	addi $sp,$sp,-76
	lw $t0,64($sp)
	sw $t0,8($sp)
	li $t0,1
	sw $t0,16($sp)
	lw $t0,8($sp)
	lw $t1,16($sp)
	beq $t0,$t1,$label0
	nop
	 j $label1
$label0:
	li $t0,1
	sw $t0,24($sp)
	lw $v1,24($sp)
	lw $ra,76($sp)
	lw $sp,72($sp)
	jr $ra
	 j $label2
$label1:
$label2:
	lw $t0,64($sp)
	sw $t0,32($sp)
	lw $t0,64($sp)
	sw $t0,40($sp)
	li $t0,1
	sw $t0,44($sp)
	lw $t0,40($sp)
	lw $t1,44($sp)
	sub $t0,$t0,$t1
	sw $t0,40($sp)
	lw $t0,40($sp)
	sw $t0,-12($sp)
	jal test_func
	sw $v1,48($sp)
	lw $t0,48($sp)
	lw $t1,32($sp)
	mult $t0,$t1
	mflo $t0
	sw $t0,32($sp)
	lw $t0,32($sp)
	sw $t0,60($sp)
	lw $t0,60($sp)
	sw $t0,56($sp)
	lw $v1,56($sp)
	lw $ra,76($sp)
	lw $sp,72($sp)
	jr $ra
	lw $ra,76($sp)
	lw $sp,72($sp)
	jr $ra
test_cycle:
	sw $sp,-4($sp)
	sw $ra,0($sp)
	addi $sp,$sp,-88
	li $t0,0
	sw $t0,8($sp)
	lw $t0,8($sp)
	sw $t0,76($sp)
$label6:
	lw $t0,76($sp)
	sw $t0,16($sp)
	li $t0,4
	sw $t0,24($sp)
	lw $t0,16($sp)
	lw $t1,24($sp)
	sub $t0,$t1,$t0
	bgtz $t0,$label4
	nop
	 j $label3
$label5:
	li $t0,1
	sw $t0,28($sp)
	lw $t0,76($sp)
	lw $t1,28($sp)
	add $t0,$t0,$t1
	sw $t0,76($sp)
	 j $label6
$label4:
	lw $t0,76($sp)
	sw $t0,36($sp)
	lw $a0,36($sp)
	li $v0,1
	syscall
	 j $label5
$label3:
$label7:
	lw $t0,76($sp)
	sw $t0,44($sp)
	lw $a0,44($sp)
	li $v0,1
	syscall
	lw $t0,76($sp)
	sw $t0,52($sp)
	li $t0,1
	sw $t0,56($sp)
	lw $t0,52($sp)
	lw $t1,56($sp)
	add $t0,$t0,$t1
	sw $t0,52($sp)
	lw $t0,52($sp)
	sw $t0,76($sp)
	lw $t0,76($sp)
	sw $t0,64($sp)
	li $t0,10
	sw $t0,72($sp)
	lw $t0,64($sp)
	lw $t1,72($sp)
	sub $t0,$t1,$t0
	bgtz $t0,$label7
	nop
	lw $ra,88($sp)
	lw $sp,84($sp)
	jr $ra
test_scanf:
	sw $sp,-4($sp)
	sw $ra,0($sp)
	addi $sp,$sp,-20
	li $v0,4
	la $a0,$str0
	syscall
	li $v0,4
	la $a0,$str1
	syscall
	li $v0,5
	syscall
	sw $v0,4($gp)
	li $v0,4
	la $a0,$str2
	syscall
	lw $t0,4($gp)
	sw $t0,8($sp)
	lw $a0,8($sp)
	li $v0,1
	syscall
	lw $ra,20($sp)
	lw $sp,16($sp)
	jr $ra
	lw $ra,20($sp)
	lw $sp,16($sp)
	jr $ra
test_array:
	sw $sp,-4($sp)
	sw $ra,0($sp)
	addi $sp,$sp,-180
	li $t0,0
	sw $t0,8($sp)
	lw $t0,8($sp)
	sw $t0,124($sp)
$label11:
	lw $t0,124($sp)
	sw $t0,16($sp)
	li $t0,10
	sw $t0,24($sp)
	lw $t0,16($sp)
	lw $t1,24($sp)
	sub $t0,$t1,$t0
	bgtz $t0,$label9
	nop
	 j $label8
$label10:
	li $t0,1
	sw $t0,28($sp)
	lw $t0,124($sp)
	lw $t1,28($sp)
	add $t0,$t0,$t1
	sw $t0,124($sp)
	 j $label11
$label9:
	lw $t0,124($sp)
	sw $t0,36($sp)
	lw $t0,124($sp)
	sw $t0,44($sp)
	lw $t0,36($sp)
	li $t1,2
	sllv $t0,$t0,$t1
	li $t1,128
	add $t1,$sp,$t1
	add $t0,$t0,$t1
	lw $t2,44($sp)
	sw $t2,0($t0)
	 j $label10
$label8:
	li $v0,4
	la $a0,$str3
	syscall
	li $t0,0
	sw $t0,52($sp)
	lw $t0,52($sp)
	sw $t0,124($sp)
$label15:
	lw $t0,124($sp)
	sw $t0,60($sp)
	li $t0,10
	sw $t0,68($sp)
	lw $t0,60($sp)
	lw $t1,68($sp)
	sub $t0,$t1,$t0
	bgtz $t0,$label13
	nop
	 j $label12
$label14:
	li $t0,1
	sw $t0,72($sp)
	lw $t0,124($sp)
	lw $t1,72($sp)
	add $t0,$t0,$t1
	sw $t0,124($sp)
	 j $label15
$label13:
	li $t0,0
	sw $t0,80($sp)
	lw $t0,80($sp)
	sw $t0,120($sp)
$label19:
	lw $t0,120($sp)
	sw $t0,88($sp)
	lw $t0,124($sp)
	sw $t0,96($sp)
	lw $t0,88($sp)
	lw $t1,96($sp)
	sub $t0,$t1,$t0
	bgtz $t0,$label17
	nop
	 j $label16
$label18:
	li $t0,1
	sw $t0,100($sp)
	lw $t0,120($sp)
	lw $t1,100($sp)
	add $t0,$t0,$t1
	sw $t0,120($sp)
	 j $label19
$label17:
	lw $t0,120($sp)
	sw $t0,112($sp)
	lw $t0,112($sp)
	li $t1,2
	sllv $t0,$t0,$t1
	li $t1,128
	add $t1,$sp,$t1
	add $t0,$t0,$t1
	lw $t1,0($t0)
	sw $t1,116($sp)
	lw $a0,116($sp)
	li $v0,1
	syscall
	 j $label18
$label16:
	li $v0,4
	la $a0,$str4
	syscall
	 j $label14
$label12:
	lw $ra,180($sp)
	lw $sp,176($sp)
	jr $ra
main:
	sw $sp,-4($sp)
	sw $ra,0($sp)
	addi $sp,$sp,-96
	 j const_lab
main_start:
	li $t0,1
	sw $t0,8($sp)
	li $t0,2
	sw $t0,12($sp)
	li $t0,3
	sw $t0,16($sp)
	lw $t0,16($sp)
	lw $t1,12($sp)
	mult $t0,$t1
	mflo $t0
	sw $t0,12($sp)
	lw $t0,8($sp)
	lw $t1,12($sp)
	add $t0,$t0,$t1
	sw $t0,8($sp)
	lw $t0,8($sp)
	sw $t0,80($sp)
	jal test_exp
	sw $v1,24($sp)
	lw $t0,24($sp)
	sw $t0,76($sp)
	lw $t0,76($sp)
	sw $t0,32($sp)
	lw $a0,32($sp)
	li $v0,1
	syscall
	lw $t0,76($sp)
	sw $t0,40($sp)
	li $t0,137
	sw $t0,48($sp)
	lw $t0,40($sp)
	lw $t1,48($sp)
	beq $t0,$t1,$label20
	nop
	 j $label21
$label20:
	li $v0,4
	la $a0,$str5
	syscall
	 j $label22
$label21:
	li $v0,4
	la $a0,$str6
	syscall
$label22:
	li $v0,4
	la $a0,$str7
	syscall
	li $v0,4
	la $a0,$str8
	syscall
	jal test_scanf
	li $v0,4
	la $a0,$str9
	syscall
	li $t0,4
	sw $t0,60($sp)
	lw $t0,60($sp)
	sw $t0,-12($sp)
	jal test_func
	sw $v1,64($sp)
	lw $t0,64($sp)
	sw $t0,80($sp)
	lw $t0,80($sp)
	sw $t0,72($sp)
	lw $a0,72($sp)
	li $v0,1
	syscall
	li $v0,4
	la $a0,$str10
	syscall
	li $v0,4
	la $a0,$str11
	syscall
	jal test_cycle
	li $v0,4
	la $a0,$str12
	syscall
	li $v0,4
	la $a0,$str13
	syscall
	li $v0,5
	syscall
	sw $v0,80($sp)
	jal test_array
	li $v0,4
	la $a0,$str14
	syscall
	lw $ra,96($sp)
	lw $sp,92($sp)
	jr $ra
end: