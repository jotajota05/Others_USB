#recibe en $a0 el angulo
#recibe en $a1 el apuntador al arreglo auxiliar
seno:
	addi $sp -12
	sw $a0 12($sp)
	sw $a1 8($sp)
	sw $ra 4($sp)
	la $s0 presicion
	lw $s1 ($s0)
#$s0 contiene la dreccion de la presicion y $s1 el valor
	move $t0 $s1
	move $s2 $a1 #$s2 contendra el apuntador al comienzo del arreglo por siempre
	li $t1 1
	move $t2 $s2
	loop_termino:
		move $a1 $t1
		move $a2 $t2
		jal termino
		addi $t1 1
		addi $t2 4
		ble $t1 $s1 loop_termino
#el arreglo auxiliar contiene todos los terminos de la serie 
	move $t0 $s2
	li $t1 0
	suma_pos:
		lw $a0 ($t0)
		move $a1 $t1
		jal float_suma
		move $t1 $v0
		addi $t0 2
		ble $t0 $s1 suma_pos
#$t1 contiene los terminos positivos
	move $t0 $s2
	addi $t0 1
	li $t2 0
	suma_neg:
		lw $a0 ($t0)
		move $a1 $t2
		jal float_suma
		move $t2 $v0
		addi $t0 2
		ble $t0 $s1 suma_pos
#$t2 contiene los terminos negativos 
	move $a0 $t1
	move $a1 $t2
	jal float_resta
	jr $ra
	
#recibe en a0 la base
#recibe en a1 el indice
potencia:
	addi $sp -12
	sw $ra 12($sp)
	sw $a0 8($sp)
	sw $a1 4($sp)
	move $s5 $a0
	move $t1 $a1
	subu $t1 1
	li $t3 1
	move $s6 $a0
	
	loop_potencia:
		move $a0 $s5 
		move $a1 $s6
		jal float_mult
		move $s5 $v0
		addi $t1 $t1 -1
		bgtz $t1 loop_potencia
	lw $ra 12($sp)
	lw $a0 8($sp)
	lw $a1 4($sp)
	addi $sp 12
	jr $ra

	
	#recibe en a0 el valor del angulo
#en a1 recibe que termino es
#en a2 donde guardarlo
termino:
	addi $sp -16
	sw $a0 16($sp)
	sw $a1 12($sp)
	sw $a2 8($sp)
	sw $ra 4($sp)
	move $s0 $a0
	move $s1 $a1
	jal potencia
	move $t1 $v0
	move $a0 $s1
	jal factorial
	move $t2 $v0
#tenemos el numerador y denominador, los pasamos a float y operamos
	#move $a0 $t1
	#li $a1 0
	#jal float_componer
	#move $t1 $v0
	move $a0 $t2
	jal float_itof
	move $t2 $v0
	move $a0 $t1
	move $a1 $t2
	jal float_div
	lw $a0 16($sp)
	lw $a1 12($sp)
	lw $a2 8($sp)
	lw $ra 4($sp)
	addi $sp 16
	jr $ra
	
#recibe en a0 el entero para devolver su factorial en v0	
factorial:
		addi $sp $sp -4
		sw $fp 4($sp)
		addi $fp $sp 4
		move $t0 $a0
		li $v0 1
		loop_factorial:
			mul $v0 $v0 $t0
			addi $t0 $t0 -1
			bgt $t0 1 loop_factorial
		lw $fp 4($sp)
		addi $sp $sp 4
		jr $ra
