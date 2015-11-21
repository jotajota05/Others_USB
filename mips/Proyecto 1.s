#Luis Rodriguez 05-38823
#Juan Garcia 05-38207
#
#Tabla de utilizacion de registros
#$t0: Sobre este registro manejamos la direccion de memoria donde esta P1
#$t1: Sobre este registro manejamos la direccion de memoria donde esta P2
#$t2: Guarda el grado de P1 
#$t3: Guarda el grado de P2. Ademas es luego utilizado como contador al 
#     imprimir los polinomios
#$t4: Almacena el entero 4 para el manejo de direcciones de memoria
#$t5: Utilizado para la construccion de la direccion de cada coeficiente.
#$t6: Almacena el resultado temporal de las multiplicaciones.
#$t7: Guarda la direccion donde se empieza a guardar el resultado.
#$t8: Utilizado para detener la impresion de los polinomios.
#$s0: Carga el pivote de P1 para multiplicarlo
#$s1: Va cargando los valores de P2 para multiplicarlos con el pivote.
#$s2: Se guarda el el resultado de la multiplicacion actual mientras se 
#     guarda en memoria.
#$s3: Guarda el grado de P1
#$s4: Guarda el grado de P2


	.data
X: 		.asciiz "x"
mas:	.asciiz "+"
p1:		.asciiz " \nP1: "
p2:		.asciiz " \nP2: "
Q:		.asciiz " \nQ: "
resultado:      .word 0

	.text
main:	
#Se cargan desde el archivo exepctions los polinomios y sus grados y sumamos
		lw $s3 g1
		lw $s4 g2
		li $t4 4
		la $t0, P1
		lw $t2, g1
		addi $t2 1

#Previamente se le sumo 1 al grado para hacer la iteracion sobre 
#todos los coeficientes y en loop 1 se pivotea sobre uno de los coeficientes
#de P1 para en loop2 multiplicarlo por todo P2

loop1: 	beqz $t2, end1
		la $t1, P2
		lw $t3, g2
		addi $t3 1
		lw $s0, 0($t0)
		
#En loop2 se calcula la posicion que tendra el resultado de cada 
#multiplicacion y se suma con el valor que ya tenia dicho coeficiente

loop2: 	beqz $t3, end2
		la $t7, resultado
		mul $t5 $t4 $t2
		add $t7 $t5 $t7
		mul $t5 $t4 $t3
		add $t7 $t5 $t7
		lw $s1, 0($t1)
		mul $s2, $s0 $s1 
		lw $t6 0($t7)
		add $s2 $t6 $s2
		sw $s2 0($t7)
		addi $t1 4
		addi $t3 -1
		b loop2
		
end2:	addi $t0 4
		addi $t2 -1
		b loop1
		
#En end1 se vuelven a cargar los datos deP1 e imprimimos su nombre

end1:	
		la $t7 P1
		la $t2 g1
		lw $t3 g1
		li $v0 4
		la $a0 p1
		syscall
		
#Se imprime P1 con sus signos las X y los coeficientes

imprimirP1:
		bltz $t3, endP1
		lw $t0 4($t7)
		sw $t3 g1
		li $v0 1
		lw $a0 0($t7)
		beqz $a0, Smas1
		syscall
		beqz $t3, endP1
		li $v0 4
		la $a0 X
		syscall
		li $v0 1
		lw $a0 0($t2)
		syscall
		blez $t0, Smas1
		li $v0 4
		la $a0 mas
		syscall
Smas1:	addi $t7 4
		addi $t3 -1
		b imprimirP1

#Carga la informacion de P2 e imprime su nombre

endP1:	
		la $t7 P2
		la $t2 g2
		lw $t3 g2
		li $v0 4
		la $a0 p2
		syscall
		
#Se imprime P2 con sus signos las X y los coeficientes
imprimirP2:
		bltz $t3, endP2
		lw $t0 4($t7)
		sw $t3 g2
		li $v0 1
		lw $a0 0($t7)
		beqz $a0, Smas2
		syscall
		beqz $t3, endP2
		li $v0 4
		la $a0 X
		syscall
		li $v0 1
		lw $a0 0($t2)
		syscall
		blez $t0, Smas2
		li $v0 4
		la $a0 mas
		syscall
Smas2:	addi $t7 4
		addi $t3 -1
		b imprimirP2
		
#Nos ubicamos en la ultima palabra de la respuesta para imprimirla

endP2:	
		la $t8 resultado+4
		add $t2 $s3 $s4
		addi $t2 2
		mul $t3 $t2 $t4
		la $t7 resultado
		add $t7 $t7 $t3
		addi $t2 -2
		sw $t2 g1
		la $t2 g1
		lw $t3 g1
		li $v0 4
		la $a0 Q
		syscall
		
#Imprime la respuesta empezando desde el final para hacerlo de mayor a menor
#de acuerdo al grado de los coeficientes

imprimirQ:
		bltz $t3, end
		lw $t0 -4($t7)
		sw $t3 g1
		beq $t8 $t7 end
		li $v0 1
		lw $a0 0($t7)
		beqz $a0, Smas3
		syscall
		beqz $t3, end
		li $v0 4
		la $a0 X
		syscall
		li $v0 1
		lw $a0 0($t2)
		syscall
		blez $t0, Smas3
		li $v0 4
		la $a0 mas
		syscall
Smas3:	addi $t7 -4
		addi $t3 -1
		b imprimirQ
		
end:	li $v0 10
		syscall
		
		
		