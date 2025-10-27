GCC = gcc
FLAGS = -lm

PROGRAMAS = taller_procesos

taller_procesos: 
		$(GCC) $@.c Funciones.c -o $@

clear: 
		$(RM) $(PROGRAMAS)
