#Primeramente se declaran cttes que van a ser usadas por el programa
#para realizar diferentes acciones, especificamente sobre la lectura
#del archivo y para las funciones que permiten obtener los campos
#de las estrellas
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
LPS=-2

#En nuestro .data, reservamos la memoria para la lectura de las estrellas
#tambien para almacenar algunos valor que nos seran util en la ejecucion
#de nuestras funciones
.data
	bienvenida: .asciiz "\nBienvenido al catalogo estelar\n"
	por: .asciiz "\npor: Juan Garcia 0538207 y Luis Rodriguez 05-38826\n"
	fileName: .asciiz "catalogo.txt"
	enter: .asciiz "\n"
	magnitud: .asciiz "\nIntroduzca una magnitud para listar las estrellas:"
	listaEste: .asciiz "\nLas estrellas de menor magnitud son:\n"
	quedesea: .asciiz "\nQue desea hacer?\n"
	opcion1: .asciiz "\n1)Conocer info de una estrella\n"
	opcion2: .asciiz "2)Imprimir estrellas menores a una magnitud\n"
	opcion3: .asciiz "3)Salir del sistema\n"
	opcion: .asciiz "Opcion:"
	error: .asciiz "\nERROR Ingrese una opcion valida\n"
	adios: .asciiz "\n Hasta Luego!! \n"
	cat: .asciiz "\nIntroduzca el # de catalogo de la estrella: "
	numCat: .asciiz "\nNumero de catalogo: "
	nombreEst: .asciiz "\nNombre:"
	horasar: .asciiz " Horas de ascencion recta\n"
	minutosar: .asciiz " Minutos de ascencion recta\n"
	segundosar: .asciiz " Segundos de ascencion recta\n"
	grados: .asciiz " Grados de declinacion\n"
	minutosda: .asciiz " Minutos de arco de declinacion\n"
	segundosda: .asciiz " Segundos de arco de declinacion\n"
	magni: .asciiz "Magnitud: "
	noexist: .asciiz "\nLa estrella solicitada no existe en el catalogo\n"
	desicion: .word 0
	.align 2
	buf: .space 36
	.word 0
	.align 2
	estLeida: .space 36
	.align 2
	name: .space 10
	estrellas: .word 0
	hash: .word 0
	nombre: .word 0 0 0 0
	tamanoT: .word 0
	
.text
	main:
	
#Primeramente se le da la bienvenida al usuario y se calculan el numero
#de estrellas a guardar y el tamaño de la tabla que usaremos para almacenar
	la $a0 bienvenida
	li $v0 4
	syscall
	la $a0 por
	li $v0 4
	syscall
	move $s0 $0
#presenta el menu de opciones ofrecidas por el programa
#guarda en desicion la opcion seleccionada
inicio:
	la $a0 quedesea
	li $v0 4
	syscall
	la $a0 opcion1
	li $v0 4
	syscall
	la $a0 opcion2
	li $v0 4
	syscall
	la $a0 opcion3
	li $v0 4
	syscall
	la $a0 opcion
	li $v0 4
	syscall
	li $v0 5
	syscall
	sw $v0 desicion
	
	bltz $s0 fin2
	
	jal tamanoTabla
	sw $v0 tamanoT
	jal numEstrellas
	sw $v0 estrellas
	move $s0 $v0
	move $a0 $v0
	
#Se procede a abrir el archivo de texto para leer
	li $v0 OPEN
	la $a0 fileName
	li $a1 0x0
	syscall
	addi $sp -4
	sw $v0 4($sp)
	move $s1 $v0
	
#Se pide bytes para almacenar las estrellas en memoria
	li $s2 36
	mul $a0 $s0 $s2
	li $v0 9
	syscall
	move $s3 $v0
	
	move $a0 $s1
	li $a1 LPS
	move $t2 $s3
	
#Los proximos dos ciclos realizan la tarea de leer de archivo las estrellas
#y a su vez ir almacenadolas en memoria, cabe acotar que almacena es la informacion
#que lee, luego se procedera a guardar en la tabla de hash los apuntadores
loop_grabarES:
	jal leerEstrella
	blez $v0 fin1
	move $t0 $v1
	li $t3 9
	
loop_salvar:
	lw $t1 0($t0)
	sw $t1 0($t2)
	addi $t0 4
	addi $t2 4
	addi $t3 -1
	beqz $t3 fin_loopsalvar
	b loop_salvar
	
fin_loopsalvar:
	
	b loop_grabarES

fin1:
	
#Se cierra el archivo, ya que se termino de leer las estrellas, y estas ya
#se encuantran en memoria
	li $v0 CLOSE
	lw $a0 4($sp)
	syscall
	addi $sp 4
	
#Ahora se procede a guardar ls datos en la tabla de Hash, cabe destacar que
#os datos que son guardados, son los apuntadores, o direcciones de memoria
#de las estrellas almacandas anterirmente
	move $a0 $s0
	move $t1 $a0
	jal inicTablaHash
	sw $v0 hash
	move $s0 $v0
	move $t2 $s3

loop_salvTabla:
	move $a0 $t2
	move $a1 $s0
	jal insertEstrella 
	addi $t2 36
	addi $t1 -1
	beqz $t1 fin2
	b loop_salvTabla

#Se carga la desicion tomada en el menu para ejecutarla
fin2:

	lw $t0 desicion
	li $t1 1
	li $t2 2
	li $t3 3
	beq $t0 $t1 info
	beq $t0 $t2 listar
	beq $t0 $t3 salir
	li $s0 -2
	la $a0 error
	li $v0 4
	syscall
	b inicio

#Se ejecuta cuando la opcion tomada es la correspondiente a buscar
#la informacion de una estrella
info:
	la $a0 enter
	li $v0 4
	syscall
	li $v0 4
	la $a0 cat
	syscall
	li $v0 5
	syscall
	move $a0 $v0
	jal informacion
	li $s0 -2
	b inicio

#Luego de salvar las estrellas en la tabla de Hash, relizamos la funcion
#que permite al usuario listar las estrellas de menor magnitud
#a la que el ingreso
listar:
	la $a0 enter
	li $v0 4
	syscall
	li $v0 4
	la $a0 magnitud
	syscall
	li $v0 6
	syscall
	mfc1 $a0 $f0
	lw $a1 hash
	jal imprimirMag
	li $s0 -2
	b inicio
	
salir:
	la $a0 adios
	li $v0 4
	syscall
	li $v0 10
	syscall

#recibe en $a0 el numero de catalogo de la estrella que se desea mostrar y la imprime 
informacion:
	addi $sp -20
	sw $fp 20($sp)
	add $fp $sp 20
	sw $ra 16($sp)
	sw $s0 12($sp)
	sw $s1 8($sp)
	sw $s2 4($sp)
	
	move $s0 $a0
	lw $a1 tamanoT
	jal funcHash
	sll $s1 $v0 3
	lw $t0 hash
	add $s1 $t0 $s1 #en s1 comienza la lista asociada al hash de nuestra estrella
	 
loop_enlista:
	lw $t1 0($s1)
	lw $t2 0($t1)
	move $a0 $t1
	jal obtNumCatalogo
	move $t2 $v0
	bne $s0 $t2 loop_sigue
	beq $s0 $t2 found
#Permite ir a la siguiente estrella si la actual no es la que buscamos
loop_sigue:
	addu $s1 $s1 4
	lw $s1 ($s1)
	beqz $s1 noexiste
	b loop_enlista
#Imprime los datos de la estrella que se pidio al encontrarla	
found: 
	la $a0 numCat
	li $v0 4
	syscall
	move $s2 $t1 #en s2 esta el apuntador a la estrella
	move $a0 $s2
	jal obtNumCatalogo
	move $a0 $v0
	li $v0 1
	syscall #impreso numero de catalogo
				
	move $a0 $s2
	jal obtNombre
	
	sw $v0 nombre
	sw $v1 nombre+4
	lh $t3 4($sp)
	addi $sp 4
	sw $t3 nombre+8
	la $a0 nombreEst
	li$v0 4
	syscall
	la $a0 nombre
	li $v0 4
	syscall#impreso todo el nombre
	la $a0 enter
	li $v0 4
	syscall
	
	move $a0 $s2
	li $a1 HascR
	jal obtEnteros
	move $a0 $v0
	li $v0 1
	syscall
	la $a0 horasar
	li $v0 4
	syscall #impresas las horas de ascencion recta
	
	move $a0 $s2
	li $a1 MascR
	jal obtEnteros
	move $a0 $v0
	li $v0 1
	syscall
	la $a0 minutosar
	li $v0 4
	syscall #impresas los minutos de ascencion recta
	
	move $a0 $s2
	li $a1 SascR
	jal obtFlotantes
	move $a0 $v0 
	jal float_imprimir
	la $a0 segundosar
	li $v0 4
	syscall #impresas las horas de ascencion recta
	
	move $a0 $s2
	li $a1 Gincl
	jal obtEnteros
	move $a0 $v0
	li $v0 1
	syscall
	la $a0 grados
	li $v0 4
	syscall#impresos los grados de declinacion
	
	move $a0 $s2
	li $a1 Marc
	jal obtEnteros
	move $a0 $v0
	li $v0 1
	syscall
	la $a0 minutosda
	li $v0 4
	syscall#impresos los minutos de arco 
	
	move $a0 $s2
	li $a1 Sarc
	jal obtEnteros
	move $a0 $v0
	li $v0 1
	syscall
	la $a0 segundosda
	li $v0 4
	syscall#impresos los minutos de arco 
	
	la $a0 magni
	li $v0 4
	syscall
	move $a0 $s2
	li $a1 Mag
	jal obtFlotantes
	move $a0 $v0 
	jal float_imprimir #impresa lamagnitud
	la $a0 enter
	li $v0 4
	syscall
	b fin
#Cuando se pide la informacion de una estrella que no esta contenida
#en el catalogo, lo informa
noexiste:
	la $a0 noexist
	li $v0 4
	syscall
fin:
	lw $s2 4($sp)
	lw $s1 8($sp)
	lw $s0 12($sp)
	lw $ra 16($sp)
	lw $fp 20($sp)
	addi $sp -20
	jr $ra 
	
#Procedimiento que me imprime las estrellas de menor magnitud
#a un valor dado
#Parametros:
#	$a0 el valor de magitud que ingresa el usuario
#	$a1 el apuntador al inicio de la tabla de hash
#Devulve:
#	No devuelve ningun valor, imprime en consola las estrellas
imprimirMag:
	addi $sp 44
	sw $fp 44($sp)
	add $fp $sp 44
	sw $ra 40($sp)
	sw $t0 36($sp)
	sw $t1 32($sp)
	sw $t2 28($sp)
	sw $t3 24($sp)
	sw $t4 20($sp)
	sw $s0 16($sp)
	sw $s1 12($sp)
	sw $s2 8($sp)
	sw $s3 4($sp)
	
	li $s2 8
	
	move $s0 $a0
	move $s1 $a1
	move $s3 $a1
	lw $v0 tamanoT
	move $t4 $v0 
	move $t5 $v0
	la $a0 listaEste
	li $v0 4
	syscall
	
#en este ciclo nos vamos moviendo a traves de la tabla de Hash, y para
#cada estrella, obtenemos su magnitud, si logra ser menor que la ingresada
#procedmos a imprimirla, si no, continuamos con la siguiente estrella
loop_In:
	
	beqz $s1 fin_loopIn
	lw $t0 0($s1)
	beqz $t0 fin_loopIn
	move $a0 $t0
	li $a1 Mag
	jal obtFlotantes
	bgt $v0 $s0 cont
	move $a0 $t0
	jal obtNombre
	sw $v0 nombre
	sw $v1 nombre+4
	lh $t3 4($sp)
	addi $sp 4
	sw $t3 nombre+8
	la $a0 nombre
	li $v0 4
	syscall
	la $a0 enter
	li $v0 4
	syscall
	lw $s1 4($s1)
	b loop_In
	lw $s1 4($s1)
	b loop_In
	
cont:
	lw $s1 4($s1)
	b loop_In
fin_loopIn:
	addi $t4 -1
	sub $t6 $t5 $t4 
	mul $t6 $t6 $s2
	add $s1 $s3 $t6
	beqz $t4 finMag
	b loop_In
	
	
finMag:
	lw $s3 4($sp)
	lw $s2 8($sp)
	lw $s1 12($sp)
	lw $s0 16($sp)
	lw $t4 20($sp)
	lw $t3 24($sp)
	lw $t2 28($sp)
	lw $t1 32($sp)
	lw $t0 36($sp)
	lw $ra 40($sp)
	lw $fp 44($sp)
	addi $sp 36
	jr $ra
	
#Procedimiento para insertar estrellas en la tabla de Hash. Segun nuestra
#funcion Hash, vamos insertando los apuntadores a la estrella en su posicion
#correcta
#Parametros:
#	$a0 el apuntador a la estrella a insertar
#	$a1 el apuntador a la tabla de Hash
#Devuelve:
#	No devuelve ningun valor, inserta en la tabla la estrella ingresada
insertEstrella:
	addi $sp 36
	sw $fp 36($sp)
	add $fp $sp 36
	sw $ra 32($sp)
	sw $t0 28($sp)
	sw $t1 24($sp)
	sw $s0 20($sp)
	sw $s1 16($sp)
	sw $s2 12($sp)
	sw $s3 8($sp)
	sw $s4 4($sp)
	
	move $s0 $a0
	move $s1 $a1
	
	lw $v0 tamanoT
	move $s2 $v0
	jal obtNumCatalogo
	move $a0 $v0
	move $a1 $s2
	jal funcHash
	move $s3 $v0
	
	
	li $t0 8
	mul $s3 $s3 $t0
	add $s1 $s1 $s3 #$s1 guarda la fila en la tabla donde va aingresar
	
	lw $t1 0($s1)
	lw $s4 4($s1)
	move $s3 $s1
	addi $s3 4
	bnez $t1 despl
	sw $s0 0($s1)
	b finI

despl:
	beqz $s4 inserto
	lw $t1 0($s4)
	move $s3 $s4
	addi $s3 4
	lw $s4 4($s4)
	bnez $t1 despl
	
inserto:
	li $v0 9
	li $a0 8
	syscall
	sw $v0 0($s3)
	sw $s0 0($v0)
	
finI:
	lw $s4 4($sp)
	lw $s3 8($sp)
	lw $s2 12($sp)
	lw $s1 16($sp)
	lw $s0 20($sp)
	lw $t1 24($sp)
	lw $t0 28($sp)
	lw $ra 32($sp)
	lw $fp 36($sp)
	addi $sp -36
	jr $ra
	
#Esta funcion permite inicializar la tabla de hash que vamos a usar, es decir
#pide la memoria para el vector de listas que vamos a usar, ya luego para las
#listas se va piediendo memoria a medida que vamos insertando
#Parametros:
#	$a0 el numero de estrellas
#Devuelve:
#	$v0 el apuntador al inicio del bloque de memoria
inicTablaHash:
	addi $sp $sp -12
	sw $fp 12($sp)
	addi $fp $sp 12
	sw $ra 8($sp)
	sw $s0 4($sp)
	
	jal numEstrellas
	move $a0 $v0
	lw $v0 tamanoT
	sll $v0 $v0 3
	move $s0 $v0
	li $v0 9
	move $a0 $s0
	syscall
	
	lw $s0 4($sp)
	lw $ra 8($sp)
	lw $fp 12($sp)
	addi $sp $sp 12
	jr $ra
	
#Entrega en $v0 el tamaño de la tabla de hash
tamanoTabla:
	addi $sp -16
	sw $fp 16($sp)
	addi $fp $sp 16
	sw $ra 12($sp)
	sw $s0 8($sp)
	sw $s1 4($sp)
	
	addi $sp -4
	sw $a0 4($sp)
	jal numEstrellas
	lw $a0 4($sp)
	addi $sp 4
	move $s1 $v0
	li $s0 5
	div $s1 $s0
	mflo $v0
	
	lw $s1 4($sp)
	lw $s0 8($sp)
	lw $ra 12($sp)
	lw $fp 16($sp)
	addi $sp  16
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
#Recibe en $a1 un entero que indica si se va a leer la estrella para insertar
#En $v0 entrega el numero de bytes leidos
#En $v1 se entrega en apuntador a la estrella leida
leerEstrella:
	addi $sp -20
	sw $fp 20($sp)
	addi $fp $sp 20
	sw $t0 16($sp)
	sw $t1 12($sp)
	sw $t2 8($sp)
	sw $t3 4($sp)
	
	move $t1 $a1
	
	la $a1, buf
	li $a2 LEN
	li $v0 READ
	syscall
	
	la $v1 buf
	li $t0 LPS
	bne $t0 $t1 fin_loopLE
	la $v1 estLeida
	la $t0 buf
	la $t1 estLeida
	li $t3 9
loopLE:
	lw $t2 0($t0)
	sw $t2 0($t1)
	addi $t0 4
	addi $t1 4
	addi $t3 -1
	beqz $t3 fin_loopLE
	b loopLE
	
fin_loopLE:
	lw $t3 4($sp)
	lw $t2 8($sp)
	lw $t1 12($sp)
	lw $t0 16($sp)
	lw $fp 20($sp)
	addi $sp 20
	jr $ra
	
#Entrega en $v0 el numero de estrellas
numEstrellas:
	addi $sp $sp -12
	sw $fp 12($sp)
	addi $fp $sp 12
	sw $ra 8($sp)
	sw $t1 4($sp)
	
	li $v0 OPEN
	la $a0 fileName
	li $a1 0x0
	syscall
	move $a0 $v0
	li $v0 50
loopNE:
	jal leerEstrella
	blez $v0 finNE
	addi $t1 1
	b loopNE
	
finNE:	
	li $v0 CLOSE
	lw $a0 4($sp)
	syscall
	
	move $v0 $t1
	lw $t1 4($sp)
	lw $ra 8($sp)
	lw $fp 12($sp)
	addi $sp $sp 12
	jr $ra
	
#Funcion que me entrega el numero de catalogo de una estrella
#Se pasa en $a0 el apuntador a la estrella
obtNumCatalogo:
	addi $sp $sp -24
	sw $fp 24($sp)
	addi $fp $sp 24
	sw $t0 20($sp)
	sw $t1 16($sp)
	sw $t2 12($sp)
	sw $s0 8($sp)
	sw $s1 4($sp)
	
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
	lw $s1 4($sp)
	lw $s0 8($sp)
	lw $t2 12($sp)
	lw $t1 16($sp)
	lw $t0 20($sp)
	lw $fp 24($sp)
	addi $sp $sp 24
	jr $ra
	
#Funcion que me entrega el nombre de una estrella
#Se pasa en $a0 el apuntador a la estrella
#Se entrega en $v0 y $v1 los primeros 8 bytes del nombre
#los restantes 2 bytes se entregan e la pila
obtNombre:
	addi $sp $sp -8
	sw $fp 8($sp)
	addi $fp $sp 8
	sw $s0 4($sp)
	
	lw $v0 4($a0)
	lw $v1 8($a0)
	lh $s7 12($a0)

	lw $s0 4($sp)
	lw $fp 8($sp)
	sh $s7 8($sp)
	addi $sp $sp 4
	jr $ra
	
#Funcion que me entrega los valores de hora y minutos
#de ascencion recta,grados,minutos y segundos de declinacion
#dependiendo de lo que se desee obtener
#Se pasa en $a0 el apuntador a la estrella
#Se pasa en $a1 el entero de dezplazamiento para obtener
#diferentes campos relacionados con enteros
obtEnteros:
	addi $sp $sp -24
	sw $fp 24($sp)
	addi $fp $sp 24
	sw $t0 20($sp)
	sw $t1 16($sp)
	sw $t2 12($sp)
	sw $s0 8($sp)
	sw $s1 4($sp)
	move $t0 $a0
	
	add $t0 $t0 $a1
	move $v0 $0
	li $s0 10
	li $s1 32
	li $t1 2
	
loop_Enteros:
	lb $t2 0($t0)
	mul $v0 $v0 $s0
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
	li $s1 Pos
	beq $t2 $s1 skipE
	mul $v0 $v0 $t1
	
skipE:
	lw $s1 4($sp)
	lw $s0 8($sp)
	lw $t2 12($sp)
	lw $t1 16($sp)
	lw $t0 20($sp)
	lw $fp 24($sp)
	addi $sp $sp 24
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
	addi $sp $sp -28
	sw $fp 28($sp)
	addi $fp $sp 28
	sw $ra 24($sp)
	sw $t0 20($sp)
	sw $t1 16($sp)
	sw $t2 12($sp)
	sw $s0 8($sp)
	sw $s1 4($sp)
	
	move $t0 $a0
	add $t0 $t0 $a1
	move $v0 $0
	move $v1 $0
	li $s0 10
	li $s1 46
	li $t1 2
	
loop_FloatPEntera:
	lb $t2 0($t0)
	ble $t2 $s1 skipF1
	mul $v0 $v0 $s0
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
	mul $v1 $v1 $s0
	addi $t2 $t2 -48
	add $v1 $v1 $t2
	addi $t1 -1
	addi $t0 1
	beqz $t1 fin_loop_Flotantes
	b loop_FloatPDecimal
	
fin_loop_Flotantes:
	beq $a1 Mag skipF3
	mul $v1 $v1 $s0
	
skipF3:
	move $a0 $v0
	move $a1 $v1
	jal float_componer
	
	lw $s1 4($sp)
	lw $s0 8($sp)
	lw $t2 12($sp)
	lw $t1 16($sp)
	lw $t0 20($sp)
	lw $ra 24($sp)
	lw $fp 28($sp)
	addi $sp $sp 28
	jr $ra
	
#recibe en $a0 el angulo
#recibe en $a1 el apuntador al arreglo auxiliar
seno:
	addi $sp -12
	sw $a0 12($sp)
	sw $a1 8($sp)
	sw $ra 4($sp)
	la $s0 NUM_TERM
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
		