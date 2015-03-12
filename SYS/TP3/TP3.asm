.model small
.stack
.data
ADCARLIB      DW	  100 dup(0)
CH1						DW	  1 dup(0)
ERRM					DB		13, 10, 'Chaine trop grande ', 13, 10, '$'
.code

debut:   
							MOV     ax,@data
							MOV     ds,ax           ;initialisation de DS
							CALL		lirech
							CALL		ecrirech
							JMP			fin
         
fin:					NOP
							MOV     ax, 4c00h
							INT     21H
							END     debut
