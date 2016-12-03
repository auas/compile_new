.data
$str0: .asciiz "\n**\n"
$str1: .asciiz "\ntest global identifier\n"
$str2: .asciiz "a1="
$str3: .asciiz " a2="
$str4: .asciiz " a3="
$str5: .asciiz " c1="
$str6: .asciiz " c2="
$str7: .asciiz "\nplease input ten numbers:"
$str8: .asciiz "the max number is:"
$str9: .asciiz "\nplease input twenty letters:"
$str10: .asciiz "\nthe letters that you have input are:"
$str11: .asciiz "\ntest expression\n"
$str12: .asciiz " "
$str13: .asciiz " "
$str14: .asciiz " "
$str15: .asciiz " "
$str16: .asciiz "\n^^^\n"
$str17: .asciiz "\n^^^\n"
$str18: .asciiz "are you ready to test your program? input 'Y' for start "
$str19: .asciiz "\nyou are not ready!\n"
$str20: .asciiz "\ntest recursion,please input a number"
$str21: .asciiz "\nthis number's factorial is "
$str22: .asciiz "\nyou have passed the test!\n"
.text
	li $s7,0x10040000
	move $fp,$sp
	jal main
	j end
const_lab:
	addi $t0,$zero,0
	sw $t0,4($gp)
	addi $t0,$zero,15
	sw $t0,8($gp)
	addi $t0,$zero,-10
	sw $t0,12($gp)
	addi $t0,$zero,43
	sw $t0,16($gp)
	addi $t0,$zero,77
	sw $t0,20($gp)
	 j main_start
factorial:
	sw $sp,-4($sp)
	sw $ra,0($sp)
	addi $sp,$sp,-64
	lw $t0,52($sp)
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
	lw $ra,64($sp)
	lw $sp,60($sp)
	jr $ra
	 j $label2
$label1:
	lw $t0,52($sp)
	sw $t0,36($sp)
	li $t0,1
	sw $t0,40($sp)
	lw $t0,36($sp)
	lw $t1,40($sp)
	sub $t0,$t0,$t1
	sw $t0,36($sp)
	lw $t0,36($sp)
	sw $t0,-12($sp)
	jal factorial
	sw $v1,44($sp)
	lw $t0,52($sp)
	sw $t0,48($sp)
	lw $t0,48($sp)
	lw $t1,44($sp)
	mult $t0,$t1
	mflo $t0
	sw $t0,44($sp)
	lw $v1,44($sp)
	lw $ra,64($sp)
	lw $sp,60($sp)
	jr $ra
$label2:
	lw $ra,64($sp)
	lw $sp,60($sp)
	jr $ra
GetMaxNum:
	sw $sp,-4($sp)
	sw $ra,0($sp)
	addi $sp,$sp,-136
	li $t0,0
	sw $t0,12($sp)
	lw $t0,12($sp)
	li $t1,2
	sllv $t0,$t0,$t1
	li $t1,64
	add $t1,$gp,$t1
	add $t0,$t0,$t1
	lw $t1,0($t0)
	sw $t1,16($sp)
	lw $t0,16($sp)
	sw $t0,124($sp)
	li $t0,1
	sw $t0,24($sp)
	lw $t0,24($sp)
	sw $t0,120($sp)
$label6:
	lw $t0,120($sp)
	sw $t0,32($sp)
	li $t0,10
	sw $t0,40($sp)
	lw $t0,32($sp)
	lw $t1,40($sp)
	sub $t0,$t1,$t0
	bgtz $t0,$label4
	nop
	 j $label3
$label5:
	li $t0,1
	sw $t0,44($sp)
	lw $t0,120($sp)
	lw $t1,44($sp)
	add $t0,$t0,$t1
	sw $t0,120($sp)
	 j $label6
$label4:
	li $v0,4
	la $a0,$str0
	syscall
	lw $t0,120($sp)
	sw $t0,56($sp)
	lw $t0,56($sp)
	li $t1,2
	sllv $t0,$t0,$t1
	li $t1,64
	add $t1,$gp,$t1
	add $t0,$t0,$t1
	lw $t1,0($t0)
	sw $t1,60($sp)
	lw $a0,60($sp)
	li $v0,1
	syscall
	lw $t0,120($sp)
	sw $t0,72($sp)
	lw $t0,72($sp)
	li $t1,2
	sllv $t0,$t0,$t1
	li $t1,64
	add $t1,$gp,$t1
	add $t0,$t0,$t1
	lw $t1,0($t0)
	sw $t1,76($sp)
	lw $t0,124($sp)
	sw $t0,84($sp)
	lw $t0,76($sp)
	lw $t1,84($sp)
	sub $t0,$t0,$t1
	bgtz $t0,$label7
	nop
	 j $label8
$label7:
	lw $t0,120($sp)
	sw $t0,96($sp)
	lw $t0,96($sp)
	li $t1,2
	sllv $t0,$t0,$t1
	li $t1,64
	add $t1,$gp,$t1
	add $t0,$t0,$t1
	lw $t1,0($t0)
	sw $t1,100($sp)
	lw $t0,100($sp)
	sw $t0,124($sp)
	 j $label9
$label8:
$label9:
	 j $label5
$label3:
	lw $t0,124($sp)
	sw $t0,108($sp)
	lw $v1,108($sp)
	lw $ra,136($sp)
	lw $sp,132($sp)
	jr $ra
	li $t0,1
	sw $t0,116($sp)
	lw $v1,116($sp)
	lw $ra,136($sp)
	lw $sp,132($sp)
	jr $ra
	lw $ra,136($sp)
	lw $sp,132($sp)
	jr $ra
Test_Global_Ident:
	sw $sp,-4($sp)
	sw $ra,0($sp)
	addi $sp,$sp,-216
	li $v0,4
	la $a0,$str1
	syscall
	li $v0,4
	la $a0,$str2
	syscall
	lw $t0,4($gp)
	sw $t0,8($sp)
	lw $a0,8($sp)
	li $v0,1
	syscall
	li $v0,4
	la $a0,$str3
	syscall
	lw $t0,8($gp)
	sw $t0,16($sp)
	lw $a0,16($sp)
	li $v0,1
	syscall
	li $v0,4
	la $a0,$str4
	syscall
	lw $t0,12($gp)
	sw $t0,24($sp)
	lw $a0,24($sp)
	li $v0,1
	syscall
	li $v0,4
	la $a0,$str5
	syscall
	lw $t0,16($gp)
	sw $t0,32($sp)
	lw $a0,32($sp)
	li $v0,11
	syscall
	li $v0,4
	la $a0,$str6
	syscall
	lw $t0,20($gp)
	sw $t0,40($sp)
	lw $a0,40($sp)
	li $v0,11
	syscall
	li $v0,4
	la $a0,$str7
	syscall
	li $t0,0
	sw $t0,48($sp)
	lw $t0,48($sp)
	sw $t0,200($sp)
$label13:
	lw $t0,200($sp)
	sw $t0,56($sp)
	li $t0,10
	sw $t0,64($sp)
	lw $t0,56($sp)
	lw $t1,64($sp)
	sub $t0,$t1,$t0
	bgtz $t0,$label11
	nop
	 j $label10
$label12:
	li $t0,1
	sw $t0,68($sp)
	lw $t0,200($sp)
	lw $t1,68($sp)
	add $t0,$t0,$t1
	sw $t0,200($sp)
	 j $label13
$label11:
	li $v0,5
	syscall
	sw $v0,204($sp)
	lw $t0,200($sp)
	sw $t0,76($sp)
	lw $t0,204($sp)
	sw $t0,84($sp)
	lw $t0,76($sp)
	li $t1,2
	sllv $t0,$t0,$t1
	li $t1,64
	add $t1,$gp,$t1
	add $t0,$t0,$t1
	lw $t2,84($sp)
	sw $t2,0($t0)
	 j $label12
$label10:
	jal GetMaxNum
	sw $v1,92($sp)
	lw $t0,92($sp)
	sw $t0,24($gp)
	li $v0,4
	la $a0,$str8
	syscall
	lw $t0,24($gp)
	sw $t0,100($sp)
	lw $a0,100($sp)
	li $v0,1
	syscall
	li $v0,4
	la $a0,$str9
	syscall
	li $t0,0
	sw $t0,108($sp)
	lw $t0,108($sp)
	sw $t0,200($sp)
$label17:
	lw $t0,200($sp)
	sw $t0,116($sp)
	li $t0,20
	sw $t0,124($sp)
	lw $t0,116($sp)
	lw $t1,124($sp)
	sub $t0,$t1,$t0
	bgtz $t0,$label15
	nop
	 j $label14
$label16:
	li $t0,1
	sw $t0,128($sp)
	lw $t0,200($sp)
	lw $t1,128($sp)
	add $t0,$t0,$t1
	sw $t0,200($sp)
	 j $label17
$label15:
	li $v0,12
	syscall
	sw $v0,68($gp)
	lw $t0,200($sp)
	sw $t0,136($sp)
	lw $t0,68($gp)
	sw $t0,144($sp)
	lw $t0,136($sp)
	li $t1,2
	sllv $t0,$t0,$t1
	li $t1,148
	add $t1,$gp,$t1
	add $t0,$t0,$t1
	lw $t2,144($sp)
	sw $t2,0($t0)
	 j $label16
$label14:
	li $v0,4
	la $a0,$str10
	syscall
	li $t0,0
	sw $t0,152($sp)
	lw $t0,152($sp)
	sw $t0,200($sp)
$label18:
	lw $t0,200($sp)
	sw $t0,164($sp)
	lw $t0,164($sp)
	li $t1,2
	sllv $t0,$t0,$t1
	li $t1,148
	add $t1,$gp,$t1
	add $t0,$t0,$t1
	lw $t1,0($t0)
	sw $t1,168($sp)
	lw $a0,168($sp)
	li $v0,11
	syscall
	lw $t0,200($sp)
	sw $t0,176($sp)
	li $t0,1
	sw $t0,180($sp)
	lw $t0,176($sp)
	lw $t1,180($sp)
	add $t0,$t0,$t1
	sw $t0,176($sp)
	lw $t0,176($sp)
	sw $t0,200($sp)
	lw $t0,200($sp)
	sw $t0,188($sp)
	li $t0,20
	sw $t0,196($sp)
	lw $t0,188($sp)
	lw $t1,196($sp)
	sub $t0,$t1,$t0
	bgtz $t0,$label18
	nop
	lw $ra,216($sp)
	lw $sp,212($sp)
	jr $ra
	lw $ra,216($sp)
	lw $sp,212($sp)
	jr $ra
Test_Char:
	sw $sp,-4($sp)
	sw $ra,0($sp)
	addi $sp,$sp,-32
	lw $t0,20($sp)
	sw $t0,8($sp)
	lw $t0,16($sp)
	sw $t0,12($sp)
	lw $t0,8($sp)
	lw $t1,12($sp)
	add $t0,$t0,$t1
	sw $t0,8($sp)
	lw $v1,8($sp)
	lw $ra,32($sp)
	lw $sp,28($sp)
	jr $ra
	lw $ra,32($sp)
	lw $sp,28($sp)
	jr $ra
Test_Expression:
	sw $sp,-4($sp)
	sw $ra,0($sp)
	addi $sp,$sp,-120
	li $t0,3
	sw $t0,8($sp)
	lw $t0,8($sp)
	sw $t0,108($sp)
	li $v0,4
	la $a0,$str11
	syscall
	li $t0,1
	sw $t0,16($sp)
	lw $t0,16($sp)
	sub $t0,$zero,$t0
	sw $t0,16($sp)
	lw $a0,16($sp)
	li $v0,1
	syscall
	li $v0,4
	la $a0,$str12
	syscall
	li $t0,97
	sw $t0,24($sp)
	li $t0,43
	sw $t0,28($sp)
	lw $t0,24($sp)
	lw $t1,28($sp)
	sub $t0,$t0,$t1
	sw $t0,24($sp)
	lw $a0,24($sp)
	li $v0,11
	syscall
	li $v0,4
	la $a0,$str13
	syscall
	li $t0,97
	sw $t0,36($sp)
	li $t0,1
	sw $t0,40($sp)
	lw $t0,36($sp)
	lw $t1,40($sp)
	sub $t0,$t0,$t1
	sw $t0,36($sp)
	lw $a0,36($sp)
	li $v0,1
	syscall
	li $v0,4
	la $a0,$str14
	syscall
	li $t0,43
	sw $t0,52($sp)
	lw $t0,52($sp)
	sw $t0,-12($sp)
	li $t0,45
	sw $t0,60($sp)
	lw $t0,60($sp)
	sw $t0,-16($sp)
	jal Test_Char
	sw $v1,64($sp)
	lw $a0,64($sp)
	li $v0,11
	syscall
	li $v0,4
	la $a0,$str15
	syscall
	li $t0,1
	sw $t0,80($sp)
	li $t0,2
	sw $t0,88($sp)
	lw $t0,88($sp)
	sw $t0,-12($sp)
	jal factorial
	sw $v1,92($sp)
	lw $t0,80($sp)
	lw $t1,92($sp)
	add $t0,$t0,$t1
	sw $t0,80($sp)
	lw $t0,108($sp)
	sw $t0,96($sp)
	lw $t0,96($sp)
	lw $t1,80($sp)
	mult $t0,$t1
	mflo $t0
	sw $t0,80($sp)
	lw $t0,80($sp)
	sw $t0,-12($sp)
	jal factorial
	sw $v1,100($sp)
	li $t0,4
	sw $t0,104($sp)
	lw $t0,104($sp)
	lw $t1,100($sp)
	div $t1,$t0
	mflo $t0
	sw $t0,100($sp)
	lw $a0,100($sp)
	li $v0,1
	syscall
	lw $ra,120($sp)
	lw $sp,116($sp)
	jr $ra
main:
	sw $sp,-4($sp)
	sw $ra,0($sp)
	addi $sp,$sp,-136
	 j const_lab
main_start:
	li $t0,3
	sw $t0,8($sp)
	lw $t0,8($sp)
	sw $t0,112($sp)
	li $t0,1
	sw $t0,24($sp)
	li $t0,2
	sw $t0,32($sp)
	lw $t0,32($sp)
	sw $t0,-12($sp)
	jal factorial
	sw $v1,36($sp)
	lw $t0,24($sp)
	lw $t1,36($sp)
	add $t0,$t0,$t1
	sw $t0,24($sp)
	lw $t0,112($sp)
	sw $t0,40($sp)
	lw $t0,40($sp)
	lw $t1,24($sp)
	mult $t0,$t1
	mflo $t0
	sw $t0,24($sp)
	lw $t0,24($sp)
	sw $t0,-12($sp)
	jal factorial
	sw $v1,44($sp)
	lw $t0,44($sp)
	sw $t0,116($sp)
	li $v0,4
	la $a0,$str16
	syscall
	lw $t0,116($sp)
	sw $t0,52($sp)
	lw $a0,52($sp)
	li $v0,1
	syscall
	lw $t0,116($sp)
	sw $t0,60($sp)
	li $t0,4
	sw $t0,64($sp)
	lw $t0,64($sp)
	lw $t1,60($sp)
	div $t1,$t0
	mflo $t0
	sw $t0,60($sp)
	lw $t0,60($sp)
	sw $t0,116($sp)
	li $v0,4
	la $a0,$str17
	syscall
	lw $t0,116($sp)
	sw $t0,72($sp)
	lw $a0,72($sp)
	li $v0,1
	syscall
	li $v0,4
	la $a0,$str18
	syscall
	li $v0,12
	syscall
	sw $v0,108($sp)
	lw $t0,108($sp)
	sw $t0,80($sp)
	li $t0,89
	sw $t0,88($sp)
	lw $t0,80($sp)
	lw $t1,88($sp)
	bne $t0,$t1,$label19
	nop
	 j $label20
$label19:
	li $v0,4
	la $a0,$str19
	syscall
	lw $ra,136($sp)
	lw $sp,132($sp)
	jr $ra
	 j $label21
$label20:
	jal Test_Global_Ident
	jal Test_Expression
	li $v0,4
	la $a0,$str20
	syscall
	li $v0,5
	syscall
	sw $v0,120($sp)
	li $v0,4
	la $a0,$str21
	syscall
	lw $t0,120($sp)
	sw $t0,100($sp)
	lw $t0,100($sp)
	sw $t0,-12($sp)
	jal factorial
	sw $v1,104($sp)
	lw $a0,104($sp)
	li $v0,1
	syscall
	li $v0,4
	la $a0,$str22
	syscall
	lw $ra,136($sp)
	lw $sp,132($sp)
	jr $ra
$label21:
end: