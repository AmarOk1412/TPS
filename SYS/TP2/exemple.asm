          .model small
          .stack
          .data
tl_gros   equ  200
premier   dw   100
second    dw   -100
gros      dw   tl_gros dup(0)
message   db   'Message a afficher',0ah,0dh, '$'

         .code
debut:   
	   mov     ax,@data
         mov     ds,ax           ;initialisation de DS
         
         mov     bx,premier
         mov     second,bx       ; second :=premier 

         mov     bx,0            ; res :=0
         
         mov     ax,1            ; 
tq:                              ;Pour i:=1 jqa premier
         cmp     ax,premier      ;
         jg      fin_tq          ;faire
         add     bx,ax           ;   res:= res + i
         add     ax,1            ;
         jmp     tq              ;fait
fin_tq:  nop
         
         end     debut
