          .model small
          .stack
          .data
A         dw   10H
B         dw   33H
message   db   'PGCD : ',0ah,0dh, '$'

         .code
debut:   
	       mov     ax,@data
         mov     ds,ax           ;initialisation de DS
         
         mov     AX,A
         mov     BX,B         ; second :=premier 

lopp:    CMP    BX,AX
         JE      fin_loop
         CMP    AX,BX     ;si A > B
         JG      AGreaterB
         SUB     BX, AX
         JMP     lopp
         
AGreaterB: SUB AX, BX          ; a-=b
           JMP lopp
         
fin_loop:  nop
           MOV     ax, 4c00h
           INT     21H
           end     debut
