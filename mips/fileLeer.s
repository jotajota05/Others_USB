OPEN= 13
READ=14
WRITE=15
CLOSE=16
LEN=20
	
	.data
fileName: .asciiz "pepe.txt"
buf:	.space 100

	
msg_fin: .asciiz "\nFIN \n"
	# Planificacion de registro
	# $s1 file descriptor
	# 
	.text
main:

	li $v0 9
	li $a0 3
	syscall
	
	# abro archivo
	
	li $v0 OPEN
	la $a0 fileName
	li $a1 0x0
	syscall

	move $s0, $v0 # respaldo descriptor

loop:
	# leo de archivo
	move $a0 $s0
	la $a1, buf
	li $a2 LEN
	li $v0 READ
	syscall

	blez $v0 fin

	sb $zero, buf($v0)
	
	li $v0 4
	la $a0 buf
	syscall

	b loop

fin:
	li $v0 4
	la $a0 msg_fin
	syscall
	
	# cierro archivo
	li $v0 CLOSE
	move $a0 $s0
	syscall
	
	# fin y retorno al house keeping
	jr $ra