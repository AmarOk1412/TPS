.model small
.stack
.data
ADCARLIB      DW	  100 dup(0)
CH1						DW	  1 dup(0)
ERRM					DB		13, 10, 'Chaine trop grande ', 13, 10, '$'
.code

printERR PROC
							MOV		DX,OFFSET ERRM
							MOV		AH,9h
							INT		21H
							RET
printERR ENDP

lirech PROC
							MOV		BX,ADCARLIB
l1:						MOV 	AH,1h																			; On lit un caractère
							INT 	21h 
							CMP		AL,13																			; tant qu'on a pas fait retour chariot
							JE		fil1
							MOV		byte ptr[BX],AL														; On sauvegarde le mot
							INC		BX																				; On passe au caractère suivant
							INC		[CH1]
							JMP		l1
fil1:					MOV		AL,'$'
							MOV		byte ptr[BX],AL														; On sauvegarde le mot					
							RET
							
lirech ENDP

ecrirech PROC
							MOV		BX,0
l2:						MOV		DL,byte ptr[BX]
							CMP		BX,[CH1]
							JE		fil2
							CMP		BX,100
							JG		fierr
							MOV 	AH,2H
							INT 	21h
							INC		BX
							JMP		l2
fierr:				CALL	printERR
							JMP		fil2
fil2:					RET

ecrirech ENDP
							
copiech PROC
							MOV		BX,[CH1]
l3:						MOV 	AH,1h																			; On lit un caractère
							INT 	21h 
							CMP		AL,13																			; tant qu'on a pas fait retour chariot
							JE		fil1
							
							MOV		byte ptr[BX],AL														; On sauvegarde le mot
							INC		BX																				; On passe au caractère suivant
							INC		[CH1]
							JMP		l1
fil3:					MOV		AL,'$'
							MOV		byte ptr[BX],AL														; On sauvegarde le mot					
							RET
ENDP

debut:   
							MOV     ax,@data
							MOV     ds,ax           ;initialisation de DS
							CALL		lirech
							CALL		ecrirech
							CALL		copiech
							CALL		ecrirech	
							JMP			fin
         
fin:					NOP
							MOV     ax, 4c00h
							INT     21H
							END     debut
