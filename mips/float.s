# Funciones sobre valores en punto flotante.
# Puede incluir este codigo en su programa.

	.text

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
