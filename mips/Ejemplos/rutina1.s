# Rutina que concatena 2 strings. Ilustra el pasaje de parametros
# por la pila.  
# Realizado por: Mariela J. Curiel
# Parámetros: las dos cadenas a concatenar (arre1 y arre2), la longitud de 
# cada una de las cadenas, el espacio donde quedará la cadena concatenada # (arre3) y el tamaño de este espacio (len3). Una llamada en alto nivel 
# sería:
#  x = concat(arre1, len1, arre2, len2, arre3, len3)
# Valor de retorno: el total de caracteres de la cadena concatenada, o -1 si 
# no hay espacio suficiente en arre3 para almacenar la cadena destino. 


.data
arre1: .asciiz "me voy de "
len1: .word 11
arre2: .asciiz "vacaciones"
len2: .word 11
arre3: .space 30
len3: .word 30
msj: .asciiz "No hay suficiente espacio"

# Planificacion de registros
# $a0: arre1; $a1: len1; $a2: arre2; $a3: len2; 
# $t0: temporal para arre3
# $t1: temporal para len3
# $t2: temporal

.text
main: la $a0, arre1 # Pasaje de parametros por registros
      lw $a1, len1
      la $a2, arre2
      lw $a3, len2
      # Pasaje de parametros por la pila 
      addi $sp, $sp, -8
      la $t0, arre3
      sw $t0, ($sp)
      lw $t0, len3
      sw $t0, 4($sp)
      jal concat
      # desempilo los parametros
      addi $sp, $sp, 8
      beq $v0, -1, error
      move $t2, $v0
      # Se imprime el string resultante
      la $a0, arre3
      li $v0, 4
      syscall
      b fin
error:la $a0, msj
      li $v0, 4
      syscall
fin: li	$v0, 10
     syscall



# Rutina Concat

concat: # Se desempilan los parametros
        lw $t0, ($sp)
        lw $t1, 4($sp)
        # Validar si el espacio para colocar la cadena destino es 
        # suficiente
        add $t2, $a1, $a3
        addi $t2, $t2, -1
        bgt $t2, $t1, finerror

        
conc1:  lb $t2, ($a0)
	beqz $t2, conc2 # No copiar el NULL del primer string
        sb $t2, ($t0)
        addi $v0, $v0, 1
        addi $a0, $a0, 1
        addi $t0, $t0, 1
        b conc1
conc2:  lb $t2, ($a2)
        sb $t2, ($t0)
        addi $v0, $v0, 1
        beqz $t2, finrut # se copia el NULL del segundo string
        addi $a2, $a2, 1
        addi $t0, $t0, 1
        b conc2 

finerror: addi $v0, $0, -1
finrut:      jr $ra 

          