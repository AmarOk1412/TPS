;
;*--------------------------------------------------------------------------
              .MODEL  SMALL
              .STACK
              .CODE
              PUBLIC  LIRECH,ECRIRECH,CONCATCH
;*------------------------------------------------------------------------
;*        DECLARATION GLOBALES
;*------------------------------------------------------------------------
              .DATA
;
;constantes pour les E/S
;
LIRCAR        EQU     1           ; code MS/DOS de la lecture de caractere
ECRCAR        EQU     2           ; code MS/DOS de l'ecriture de caractere
;
;constantes du module
;
TMAX          EQU     100         ; taille de la zone de stockage
FIN_CH        EQU     0DH         ; code de fin de chaine en saisie (CR)
;
VRAI          EQU     1           ; code de vrai
FAUX          EQU     0           ; code de faux
;
D_TAILLE      EQU     0           ; dep. pour champ "taille" du desc.
D_AD          EQU     2           ; dep. pour champ "adresse" du desc.
;
;variables globales du module
;
ZONECAR       DB      TMAX DUP (?)    ; zone de stockage des caracteres

ADCARLIB      DW      TMAX            ; Nombre de caracteres libres restant
              DW      OFFSET ZONECAR  ; ad. 1er car. libre dans ZONECAR
              
;
;*
;*------------------------------------------------------------------------
;*SOUS-PROGRAMME      EcrireCH
;*------------------------------------------------------------------------
;* 
;*-------------------------------------------------------------------------
              .DATA
ech_ch        equ     4
ech_TPARAM    equ     4

              .CODE

ECRIRECH:     push    bp
              mov     bp,sp

              PUSH    AX
              PUSH    BX
              push    di
              PUSH    SI
                 
              mov     bx,[BP]+ech_ch+D_AD;
              MOV     SI,0        ;
              MOV     CX,[BP]+ech_ch+D_TAILLE;
	
ECH_repeter:						; repeter jqa debordement ou fin suite							
							MOV		DL,[BX+SI]							
							MOV 	AH,2H
							INT 	21h
							ADD 	SI,1

							CMP		CX,SI									; Si CX = 0, on est à la fin de la ligne
							JNE		ECH_repeter
              
ECH_FIN:

              POP     SI
              pop     di
              POP     BX
              POP     AX
              
              pop     bp
              RET     ECH_Tparam

;
;*
;*------------------------------------------------------------------------
;*SOUS-PROGRAMME      Lirech
;*------------------------------------------------------------------------
;* 
;*-------------------------------------------------------------------------
              .DATA
lch_ch        equ     4
lch_err       equ     6
lch_TPARAM    equ     4

              .CODE

LIRECH:       push    bp
              mov     bp,sp

              PUSH    AX
              PUSH    Bx
              push    di
              PUSH    SI
              PUSH 		CX
                 
              mov     bx,ADCARLIB+D_Ad ;
              MOV     SI,0        ;
              MOV     CX,adcarlib+D_taille ;
	
LCH_repeter:						; repeter jqa debordement ou fin suite
	
              MOV     AH,LIRCAR			;    lire caractere	
              INT     21H				;  
	  
              CMP     AL,FIN_CH			;    qd car. lu = fin_ch --> fin suite
              JE      LCH_LURC			;
	
              CMP     CX,0				;
              JE      LCH_DEB
	
              SUB     CX,1				;    decremente TRESTE
	
              MOV     [BX+SI],AL			;    stocke car. lu et met a jour
              ADD     SI,1				;    l'index
	
              JMP     LCH_repeter			; fin repeter
LCH_LURC:                             
							;--> On a lu "retour charriot"
              mov     bx,ADCARLIB+D_ad		;      met a jour le descripteur
              mov     di,[bp]+lch_ch
              MOV     [di]+D_ad,bx    ;
              MOV     [di]+D_TAILLE,SI;

              ADD     ADCARLIB+D_Ad,SI		;   incremente ADCARLIB
              sub     adcarlib+D_Taille,si

              mov     bx,[bp]+lch_err ; 
              MOV     byte ptr[BX],Faux          ;   erreur:=faux        
              JMP     LCH_FIN                    ;
LCH_DEB:
              mov     BX,[bp]+lch_ch             ;--> debordement
              MOV     word ptr [BX]+D_TAILLE,0   ;       met taille=0 dans 
                                                 ;       le desc
            
              mov     BX,[bp]+LCH_ERR            ;
              MOV     byte ptr[BX],vrai          ;   erreur:=vrai
LCH_FIN:

							POP 		CX
              POP     SI
              pop     di
              POP     BX
              POP     AX
              
              pop     bp
              RET     LCH_Tparam
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
;
;*
;*------------------------------------------------------------------------
;*SOUS-PROGRAMME      ConcatCH
;*------------------------------------------------------------------------
;* 
;*-------------------------------------------------------------------------
              .DATA
cch_ch        equ     4
cch_err       equ     6
cch_TPARAM    equ     4

              .CODE

CONCATCH:       push    bp
              mov     bp,sp

              PUSH    AX
              PUSH    Bx
              push    di
              PUSH    SI
                 
              mov     bx,ADCARLIB+D_Ad ;
              MOV     SI,0        ;
              MOV     CX,adcarlib+D_taille ;
	
CCH_repeter:	JMP			CCH_FIN
CCH_FIN:

              POP     SI
              pop     di
              POP     BX
              POP     AX
              
              pop     bp
              RET     LCH_Tparam


          END
          
          

