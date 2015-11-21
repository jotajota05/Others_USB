OPEN= 13
READ=14
WRITE=15
CLOSE=16
LEN=36
HascR=14
MascR=16
SascR=18
Gincl=23
Marc=25
Sarc=27
Mag=29
Pos=43
Nega=45

.data
	fileName: .asciiz "catalogo.txt"
	.align 2
	buf: .space 50
	.align 2
	name: .space 10
	estrellas: .word 0
	
.text
	main:
	
	# abro archivo
	li $v0 OPEN
	la $a0 fileName
	li $a1 0x0
	syscall
	addi $sp -4
	sw $v0 0($sp)
	
	move $a0 $v0
	#jal numEstrellas
	move $a0 $v0
	#jal inicTablaHash
	
	li $v0 9
	li $a0 40
	syscall
	
	li $t0 50
	li $t1 100
	sw $t0 0($v0)
	sw $t1 4($v0)
	
	# cierro archivo
	li $v0 CLOSE
	lw $a0 4($sp)
	syscall
	addi $sp 4
	
	li $v0 10
	syscall
	


#Recibe en $a0 el numero de estrellas
#Pide la memoria dinamica para la tabla y entrega en $v0 el apuntador
#al inicio del bloque de memoria
inicTablaHash:
	addi $sp $sp -12
	sw $fp 12($sp)
	addi $fp $sp 12
	sw $ra 8($sp)
	sw $s0 4($sp)
	
	jal tamanoTabla
	sll $v0 $v0 2
	move $s0 $v0
	li $v0 9
	move $a0 $s0
	syscall
	
	lw $s0 4($sp)
	lw $ra 8($sp)
	lw $fp 12($sp)
	addi $sp $sp 8
	jr $ra
	
#Recibe en $a0 el numero de estrellas
#Entrega en $v0 el tamaño de la tabla de hash
tamanoTabla:
	addi $sp $sp -4
	sw $fp 4($sp)
	addi $fp $sp 4
	
	li $s0 5
	div $a0 $s0
	mflo $v0

	lw $fp 4($sp)
	addi $sp $sp 4
	jr $ra

#Recibe en $a0 el numero de catalogo de la estrella
#Recibe en $a1 el tamaño de la tabla
#Entrega en $v0 la clave correspondiente a la estrella
funcHash:
	addi $sp $sp -4
	sw $fp 4($sp)
	addi $fp $sp 4
	
	div $a0 $a1
	mfhi $v0
	
	lw $fp 4($sp)
	addi $sp $sp 4
	jr $ra
	

#Procedimiento que realiza la lectura del archivo
#Se le pasa en $a0 el descriptor
#En $v0 entrega el numero de bytes leidos
#En $v1 se entrega en apuntador a la estrella leida
leerEstrella:
	addi $sp $sp -4
	sw $fp 4($sp)
	addi $fp $sp 4
	
	la $a1, buf
	li $a2 LEN
	li $v0 READ
	syscall
	sb $zero, buf($v0)
	la $v1 buf
	
	lw $fp 4($sp)
	addi $sp $sp 4
	jr $ra
	
#recibe en $a0 el descriptor del archivo
#Entrega en $v0 el numero de estrellas
numEstrellas:
	addi $sp $sp -8
	sw $fp 8($sp)
	addi $fp $sp 8
	sw $ra 4($sp)
	
loopNE:
	jal leerEstrella
	blez $v0 finNE
	addi $t1 1
	b loopNE
	
finNE:	
	move $v0 $t1
	lw $ra 4($sp)
	lw $fp 8($sp)
	addi $sp $sp 8
	jr $ra
	
#Funcion que me entrega el numero de catalogo de una estrella
#Se pasa en $a0 el apuntador a la estrella
obtNumCatalogo:
	addi $sp $sp -4
	sw $fp 4($sp)
	addi $fp $sp 4
	
	move $t0 $a0
	move $v0 $0
	li $s0 10
	li $s1 32
	li $t1 4
	
loop_numCat:
	lb $t2 0($t0)
	beq $t2, $s1, skipC
	mul $v0 $v0 $s0
	addi $t2 $t2 -48
	add $v0 $v0 $t2
	
skipC:
	addi $t1 -1
	addi $t0 1
	beqz $t1 fin_loop_numCat
	b loop_numCat
	
fin_loop_numCat:
	
	lw $fp 4($sp)
	addi $sp $sp 4
	jr $ra
	
#Funcion que me entrega el nombre de una estrella
#Se pasa en $a0 el apuntador a la estrella
#Se entrega en $v0 y $v1 los primeros 8 bytes del nombre
#los restantes 2 bytes se entregan e la pila
obtNombre:
	addi $sp $sp -4
	sw $fp 4($sp)
	addi $fp $sp 4
	
	lw $v0 4($a0)
	lw $v1 8($a0)
	lh $s0 12($a0)

	lw $fp 4($sp)
	sh $s0 4($sp)
	jr $ra
	
#Funcion que me entrega los valores de hora y minutos
#de ascencion recta,grados,minutos y segundos de declinacion
#dependiendo de lo que se desee obtener
#Se pasa en $a0 el apuntador a la estrella
#Se pasa en $a1 el entero de dezplazamiento para obtener
#diferentes campos relacionados con enteros
obtEnteros:
	addi $sp $sp -4
	sw $fp 4($sp)
	addi $fp $sp 4
	move $t0 $a0
	
	add $t0 $t0 $a1
	move $v0 $0
	li $s1 10
	li $s2 32
	li $t1 2
	
loop_Enteros:
	lb $t2 0($t0)
	mul $v0 $v0 $s1
	addi $t2 $t2 -48
	add $v0 $v0 $t2
	addi $t1 -1
	addi $t0 1
	beqz $t1 fin_loop_Enteros
	b loop_Enteros
	
fin_loop_Enteros:
	li $t1 -1
	bne $a1 Gincl skipE
	lb $t2 -3($t0)
	li $s2 Pos
	beq $t2 $s2 skipE
	mul $v0 $v0 $t1
	
skipE:
	lw $fp 4($sp)
	addi $sp $sp 4
	jr $ra
	
#Funcion que me entrega los valores de segundos de ascension recta
#y la magnitud de la estrella
#dependiendo de lo que se desee obtener
#Se pasa en $a0 el apuntador a la estrella
#Se pasa en $a1 el entero de dezplazamiento para obtener
#diferentes campos relacionados con flotantes
#Entrega en v0 el flotante correspondiente a los segundos de ascension recta
#y a la magnitud
obtFlotantes:
	addi $sp $sp -8
	sw $fp 8($sp)
	addi $fp $sp 8
	sw $ra 4($sp)
	
	move $t0 $a0
	add $t0 $t0 $a1
	move $v0 $0
	move $v1 $0
	li $s1 10
	li $s2 46
	li $t1 2
	
loop_FloatPEntera:
	lb $t2 0($t0)
	ble $t2 $s2 skipF1
	mul $v0 $v0 $s1
	addi $t2 $t2 -48
	add $v0 $v0 $t2
	
skipF1:
	addi $t1 -1
	addi $t0 1
	beqz $t1 skipF2
	b loop_FloatPEntera
	
skipF2:
	addi $t0 1
	addi $t1 2
	beq $a1 Mag loop_FloatPDecimal
	addi $t1 -1
	
loop_FloatPDecimal:
	lb $t2 0($t0)
	mul $v1 $v1 $s1
	addi $t2 $t2 -48
	add $v1 $v1 $t2
	addi $t1 -1
	addi $t0 1
	beqz $t1 fin_loop_Flotantes
	b loop_FloatPDecimal
	
fin_loop_Flotantes:
	beq $a1 Mag skipF3
	mul $v1 $v1 $s1
	
skipF3:
	move $a0 $v0
	move $a1 $v1
	jal float_componer
	
	lw $ra 4($sp)
	lw $fp 8($sp)
	addi $sp $sp 8
	jr $ra

# Suma dos numeros de punto flotante.
# Parametros:
#   $a0: Primer operando
#   $a1: Segundo operando
# Devuelve:
#   $v0: Suma de $a0 y $a1 representada en punto flotante
float_suma:	subu $sp, $sp, 12
		sw $fp, 12($sp)
		s.s $f0, 8($sp)
		s.s $f1, 4($sp)
		
		mtc1 $a0, $f0
		mtc1 $a1, $f1
		add.s $f0, $f0, $f1
		mfc1 $v0, $f0

		lw $fp, 12($sp)
		l.s $f0, 8($sp)
		l.s $f1, 4($sp)
		addu $sp, $sp, 12
		jr $ra

# Resta dos numeros de punto flotante.
# Parametros:
#   $a0: Primer operando
#   $a1: Segundo operando
# Devuelve:
#   $v0: Diferencia de $a0 menos $a1 representada en punto flotante
float_resta:	subu $sp, $sp, 12
		sw $fp, 12($sp)
		s.s $f0, 8($sp)
		s.s $f1, 4($sp)
		
		mtc1 $a0, $f0
		mtc1 $a1, $f1
		sub.s $f0, $f0, $f1
		mfc1 $v0, $f0

		lw $fp, 12($sp)
		l.s $f0, 8($sp)
		l.s $f1, 4($sp)
		addu $sp, $sp, 12
		jr $ra

# Multiplica dos numeros de punto flotante.
# Parametros:
#   $a0: Primer operando
#   $a1: Segundo operando
# Devuelve:
#   $v0: Producto de $a0 y $a1 representado en punto flotante
float_mult:	subu $sp, $sp, 12
		sw $fp, 12($sp)
		s.s $f0, 8($sp)
		s.s $f1, 4($sp)
		
		mtc1 $a0, $f0
		mtc1 $a1, $f1
		mul.s $f0, $f0, $f1
		mfc1 $v0, $f0

		lw $fp, 12($sp)
		l.s $f0, 8($sp)
		l.s $f1, 4($sp)
		addu $sp, $sp, 12
		jr $ra

# Divide dos numeros de punto flotante.
# Parametros:
#   $a0: Dividendo
#   $a1: Divisor
# Devuelve:
#   $v0: Cociente de $a0 y $a1 representado en punto flotante
float_div:	subu $sp, $sp, 12
		sw $fp, 12($sp)
		s.s $f0, 8($sp)
		s.s $f1, 4($sp)
		
		mtc1 $a0, $f0
		mtc1 $a1, $f1
		div.s $f0, $f0, $f1
		mfc1 $v0, $f0

		lw $fp, 12($sp)
		l.s $f0, 8($sp)
		l.s $f1, 4($sp)
		addu $sp, $sp, 12
		jr $ra

# Imprime en la consola el valor de un numero de punto flotante.
# Parametros:
#   $a0: Numero a imprimir
float_imprimir:	subu $sp, $sp, 8
		sw $fp, 8($sp)
		s.s $f12, 4($sp)
		
		mtc1 $a0, $f12
		li $v0, 2
		syscall
	
		lw $fp, 8($sp)
		l.s $f12, 4($sp)
		addu $sp, $sp, 8
		jr $ra

# Construye un numero flotante a partir de su parte entera 
# y su parte decimal. 
# Parametros:
#   $a0: parte entera
#   $a1: parte decimal (representada como un 
#	entero igual al numero de centecimas)
#	Ejemplo
#       Si el valor es 5.03, $a0=5, $a1=3
#       Si el valor es 5.3,  $a0=5, $a1=30
# Devuelve:
#   $v0: El valor flotante de $a0.$a1
	
float_componer:	subu $sp, $sp, 16
		sw $fp, 16($sp)
		s.s $f0,12($sp)
		s.s $f1, 8($sp)
		s.s $f2, 4($sp)
		
		mtc1 $a0, $f0
		mtc1 $a1, $f1
	
		cvt.s.w $f0 $f0
		cvt.s.w $f1 $f1

		li $t0 100

		mtc1 $t0, $f2 
		cvt.s.w $f2 $f2

		div.s $f1, $f1, $f2
		
		add.s $f0, $f0, $f1
		mfc1 $v0, $f0

		lw $fp, 16($sp)
		l.s $f0,12($sp)
		l.s $f1, 8($sp)
		l.s $f2, 4($sp)
		addu $sp, $sp, 16
		jr $ra


# Construye un numero flotante a partir de un entero
# Parametros:
#   $a0: numero entero
# Devuelve:
#   $v0: El valor $a0 en punto flotante
	
float_itof:	subu $sp, $sp, 8
		sw $fp, 8($sp)
		s.s $f0,4($sp)
		
		mtc1 $a0, $f0

		cvt.s.w $f0 $f0

		mfc1 $v0, $f0

		lw $fp, 8($sp)
		l.s $f0,4($sp)
		addu $sp, $sp, 8
		jr $ra
		