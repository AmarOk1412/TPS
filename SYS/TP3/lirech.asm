;*------------------------------------------------------------------------
;*MODULE                      TP3 - Manipulation de chaînes de caratères
;*------------------------------------------------------------------------
;* Auteur(s) : Sébastien Blin, Collin Pierre-Henri
;*-------------------------------------------------------------------------
;*OBJET
;*      Ce programme offre des procédures de manipulation de chaînes de caractères.
;*		Ces chaînes sont déclarées comme des variables du programme.
;*		Initialement une chaîne est vide.
;*      
;*POINTS d'ENTREE
;*      
;*DONNEES EXPORTEES
;*      
;*REFERENCES EXTERNES
;*      
;*--------------------------------------------------------------------------
;*PROCEDURES :
;*      LIRECH    : Lit des caractères jusqu'à la rencontre du retour chariot et affecte les
;*					caractères lus (non compris retour-chariot) à la chaîne CH. En cas d'anomalie
;*					la chaîne résultat est vide et erreur vaut VRAI, sinon erreur vaut FAUX.
;*      ECRIRECH  : Affiche la suite de caractères de la chaîne CH.
;*      CONCATCH  :	Affecte, en utilisant la procédure COPIECH, à CHR le résultat de la 
;*					concaténation de CH1 et CH2; CH1 et CH2 ne sont pas modifiées.
;*					Le descripteur CHR doit etre différent de CH1 et CH2. EN cas d'anomalie 
;*					la chaîne résultat est vide et erreur vaut VRAI, sinon erreur vaut FAUX. 
;*		COPIECH	  :	Recopie la chaîne de caratères CH1 dans la zone de stockage.
;*-------------------------------------------------------------------------

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
LIRCAR        EQU     1           			; code MS/DOS de la lecture de caractere
ECRCAR        EQU     2           			; code MS/DOS de l'ecriture de caractere
;
;constantes du module
;
TMAX          EQU     100         			; taille de la zone de stockage
FIN_CH        EQU     0DH         			; code de fin de chaine en saisie (CR)
;
VRAI          EQU     1           			; code de vrai
FAUX          EQU     0			  					; code de faux
;
D_TAILLE      EQU     0           			; dep. pour champ "taille" du desc.
D_AD          EQU     2           			; dep. pour champ "adresse" du desc.
;
;variables globales du module
;
ZONECAR       DB      TMAX DUP (?)    		; zone de stockage des caracteres

ADCARLIB      DW      TMAX            		; Nombre de caracteres libres restant
              DW      OFFSET ZONECAR			; ad. 1er car. libre dans ZONECAR
;
;*
;*-----------------------------------------------------------------------
;*PROCEDURE     LIRECH
;*------------------------------------------------------------------------
;* 
;*------------------------------------------------------------------------
              .DATA
lch_ch        equ     4
lch_err       equ     6
lch_TPARAM    equ     4

              .CODE

LIRECH:       PUSH    bp
              MOV     bp,sp

              PUSH    AX
              PUSH		BX
              PUSH		DI
              PUSH		SI
             
                 
              MOV     BX,ADCARLIB+D_Ad
              MOV     SI,0
              MOV     CX,adcarlib+D_taille
			  
	
LCH_repeter:																		; repeter jqa debordement ou fin suite
	
              MOV     AH,LIRCAR									;    lire caractere	
              INT     21H	
	  
              CMP     AL,FIN_CH									;    qd car. lu = fin_ch --> fin suite
              JE      LCH_LURC							
	
              CMP     CX,0										
              JE      LCH_DEB										;    qd TRESTE=0 --> debordement
	
              SUB     CX,1											;    decremente TRESTE
	
              MOV     [BX+SI],AL								;    stocke car. lu et met a jour
              ADD     SI,1											;    l'index
	
              JMP     LCH_repeter								; fin repeter
			  
LCH_LURC:                             
			;--> On a lu "retour charriot"
							
              MOV     bx,ADCARLIB+D_ad					;   met a jour le descripteur
              MOV     di,[bp]+lch_ch				
              MOV     [di]+D_ad,bx    			
              MOV     [di]+D_TAILLE,SI			

              ADD     ADCARLIB+D_Ad,SI					;   mise à jour de ADCARLIB
              SUB     adcarlib+D_Taille,si		

              MOV     BX,[bp]+lch_err			 
              MOV     byte ptr[BX],Faux      	 	;   erreur:=faux        
              JMP     LCH_FIN       
			  
LCH_DEB:
              MOV     BX,[bp]+lch_ch            ;--> debordement
              MOV     word ptr [BX]+D_TAILLE,0  ;       met taille=0 dans 
                                                ;       le desc
            
              MOV     BX,[bp]+LCH_ERR           ;
              MOV     byte ptr[BX],vrai         ;   erreur:=vrai
			  
LCH_FIN:

              POP     SI
              POP     di
              POP     BX
              POP     AX
              
              POP     bp
              RET     LCH_Tparam

			  
;*
;*------------------------------------------------------------------------
;*PROCEDURE      ECRIRECH
;*------------------------------------------------------------------------
;* 
;*------------------------------------------------------------------------

.DATA
ech_ch equ 4
ech_TPARAM equ 4

.CODE

ECRIRECH: push bp
					mov bp,sp

					PUSH AX
					PUSH BX
					PUSH DI
					PUSH SI

					MOV BX,[BP]+ech_ch+D_AD;
					MOV SI,0 ;
					MOV CX,[BP]+ech_ch+D_TAILLE;

ECH_repeter: ; repeter jqa debordement ou fin suite
					MOV DL,[BX+SI]
					MOV AH,2H
					INT 21h
					ADD SI,1

					CMP CX,SI ; Si CX = 0, on est à la fin de la ligne
					JNE ECH_repeter

ECH_FIN:
					POP SI
					POP DI
					POP BX
					POP AX

					pop bp
					RET

;*
;*------------------------------------------------------------------------
;*PROCEDURE      CONCATCH
;*------------------------------------------------------------------------
;* DON'T WORK
;*------------------------------------------------------------------------

              .DATA
Concatch_ch1        equ     4
Concatch_ch2				equ			6
Concatch_ch					equ			8
Concatch_err   	    equ     10

              .CODE
CONCATCH:
							PUSH	BP
							MOV		BP,SP
			
							PUSH	AX 
							PUSH	BX
							PUSH	DX
							PUSH	SI											; entête
							
							
							MOV		BX, ADCARLIB+D_AD
							PUSH 	Concatch_ch
							CALL 	COPIECH
							POP		AX
							PUSH 	Concatch_ch2
							CALL 	COPIECH
							POP		AX
							
							MOV		DI,Concatch_ch+D_AD
							MOV 	DI,BX
							MOV		DI,Concatch_ch+D_TAILLE
							MOV		DI,5
							
COCH_FIN:			
							POP 	SI
							POP		DX
							POP		BX
							POP		AX					;prologue
							POP		BP	
							RET




;*
;*------------------------------------------------------------------------
;*PROCEDURE      COPIECH
;*------------------------------------------------------------------------
;* 
;*------------------------------------------------------------------------
              .DATA
c_ch        equ     4

              .CODE
COPIECH:
							PUSH	BP
							MOV		BP,SP
			
							PUSH	AX 
							PUSH	BX
							PUSH	DX
							PUSH	SI											; entête
        		
            	MOV   BX,[BP]+c_ch+D_AD						; Bx=adr de la chaine 00BD
							MOV		SI,0			; Si=incrémenteur
			
CCH_repeter:
							MOV   di,ADCARLIB+D_Ad
							MOV		CX,[BX+SI]	
              MOV   [di],CX
              ADD   ADCARLIB+D_Ad,1
							INC		SI											; On incrémente 
							CMP   SI,[bp]+c_ch+D_TAILLE		;    si SI = taille de la chaîne
              JNE   CCH_repeter							;	on finit la procédure
			
CCH_FIN:		
							POP 	SI
							POP		DX
							POP		BX
							POP		AX					;prologue
							POP		BP	
							RET

;*-----------------------------------------------------------------------
;* 
;*-----------------------------------------------------------------------

          END
