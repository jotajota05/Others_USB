# Rutina OCURRENCIA: busca todas las ocurrencias de un caracter 
# en una cadena de caracteres.
# Parámetros
# $a0: direccion de comienzo de la cadena 
# $a1: caracter a buscar
# DEvuelve:
# $v0: numero e ocurrencias del caracter en la cadena
# Observaciones: se apoya en la rutina find desarrollada anteriormente.


.data
str: .asciiz "la cadena de caracteres"
c:   .asciiz "a"

.text
main:
  la $a0, str
  lb $a1, c
  jal ocurrencia
  # Muevo el valor de retorno a $t2 porque $v0 va a ser modificado
  # antes de salir del programa y conviene saber el valor de retorno para 
  # estar seguros que el programa se ejecuto correctamente. 
  move $t2, $v0
fin: li	$v0, 10
  syscall


ocurrencia: 
  addi $sp, $sp, -8
  sw $s0, ($sp)
  # salvo la direccion de retorno
  sw $ra, 4($sp)
  move $s0, $0
lazo:
  jal find
  lb $t0, ($v0)
  beqz $t0, finocur
  addi $a0, $v0, 1
  addi $s0, $s0, 1
  b lazo
finocur:
  move $v0, $s0
  lw $s0, ($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  jr $ra

find: lb $t0, ($a0)
      beqz $t0, finrut
      beq $t0, $a1, finrut
      addi $a0, $a0, 1
      b find
finrut:
      add $v0, $a0, $0
       jr $ra 



