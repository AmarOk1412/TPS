.model small
.stack
.data
ADCARLIB      DW   100 dup(0)
CH1						DW   1 dup(0)
.code

lirech PROC
l1:						MOV 	AH,1h
							INT 	21h 
							CMP		AL,13
							JE		fil1
							JMP		l1
fil1:					RET							
lirech ENDP

debut:   
							MOV     ax,@data
							MOV     ds,ax           ;initialisation de DS
							CALL		lirech		
							JMP			fin
         
fin:					NOP
							MOV     ax, 4c00h
							INT     21H
							END     debut
