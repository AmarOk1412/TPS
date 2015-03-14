;*------------------------------------------------------------------------
;*MODULE                      TP3 - Manipulation de cha�nes de carat�res
;*------------------------------------------------------------------------
;* Auteur(s) : S�bastien Blin, Collin Pierre-Henri
;*-------------------------------------------------------------------------
;*OBJET
;*      Ce programme offre des proc�dures de manipulation de cha�nes de caract�res.
;*		Ces cha�nes sont d�clar�es comme des variables du programme.
;*		Initialement une cha�ne est vide.
;*      
;*POINTS d'ENTREE
;*      
;*DONNEES EXPORTEES
;*      
;*REFERENCES EXTERNES
;*      
;*--------------------------------------------------------------------------
;*PROCEDURES :
;*      LIRECH    : Lit des caract�res jusqu'� la rencontre du retour chariot et affecte les
;*					caract�res lus (non compris retour-chariot) � la cha�ne CH. En cas d'anomalie
;*					la cha�ne r�sultat est vide et erreur vaut VRAI, sinon erreur vaut FAUX.
;*      ECRIRECH  : Affiche la suite de caract�res de la cha�ne CH.
;*      CONCATCH  :	Affecte, en utilisant la proc�dure COPIECH, � CHR le r�sultat de la 
;*					concat�nation de CH1 et CH2; CH1 et CH2 ne sont pas modifi�es.
;*					Le descripteur CHR doit etre diff�rent de CH1 et CH2. EN cas d'anomalie 
;*					la cha�ne r�sultat est vide et erreur vaut VRAI, sinon erreur vaut FAUX. 
;*		COPIECH	  :	Recopie la cha�ne de carat�res CH1 dans la zone de stockage.
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
FAUX          EQU     0			  			; code de faux
;
D_TAILLE      EQU     0           			; dep. pour champ "taille" du desc.
D_AD          EQU     2           			; dep. pour champ "adresse" du desc.
;
;variables globales du module
;
ZONECAR       DB      TMAX DUP (?)    		; zone de stockage des caracteres

ADCARLIB      DW      TMAX            		; Nombre de caract�res libres restant
              DW      OFFSET ZONECAR		; ad. 1er car. libre dans ZONECAR
;
;*
;*------------------------------------------------------------------------
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
							
              MOV     bx,ADCARLIB+D_ad					;      met a jour le descripteur
              MOV     di,[bp]+lch_ch				
              MOV     [di]+D_ad,bx    			
              MOV     [di]+D_TAILLE,SI			

              ADD     ADCARLIB+D_Ad,SI					;   mise � jour de ADCARLIB
              SUB     adcarlib+D_Taille,si		

              MOV     BX,[bp]+lch_err			 
              MOV     byte ptr[BX],Faux      	 ;   erreur:=faux        
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
ech_ch        equ     4

.CODE
ECRIRECH:
							PUSH	BP
							MOV		BP,SP
			
							PUSH	AX 
							PUSH	BX
							PUSH	DX
							PUSH	SI											; ent�te
        		
            	MOV  	BX, [BP]+ech_ch+D_AD		; Bx=adr de la chaine
							MOV		SI,0										; Si=incr�menteur
			
ECH_repeter:
							MOV		AH,2H					
							MOV		DL, [bx+si]							; on affiche le caract�re courant
							INT		21H									
			
							INC		SI											; On incr�mente 
							CMP   SI,[bp]+ech_ch+d_taille	;    si SI = taille de la cha�ne
            	JNE   ECH_repeter							;	on finit la proc�dure
			
			
			
ECH_FIN:			
							POP 	SI
							POP		DX
							POP		BX
							POP		AX					;prologue
							POP		BP	
							RET

;*
;*------------------------------------------------------------------------
;*PROCEDURE      CONCATCH
;*------------------------------------------------------------------------
;* 
;*------------------------------------------------------------------------

              .DATA
Concatch_ch1        equ     4
Concatch_ch2		equ		?
Concatch_ch			equ		?
Concatch_err       equ     6

              .CODE
CONCATCH:




;*
;*------------------------------------------------------------------------
;*PROCEDURE      COPIECH
;*------------------------------------------------------------------------
;* 
;*------------------------------------------------------------------------
              .DATA
Copiech_ch        equ     4

              .CODE
COPIECH:
			PUSH	BP							;
			MOV		BP,SP						;ent�te
			PUSH AX BX SI						; 
			
			
			
			


			POP SI BX AX						;prologue
			POP BP								;


;*-----------------------------------------------------------------------
;* 
;*-----------------------------------------------------------------------

          END
