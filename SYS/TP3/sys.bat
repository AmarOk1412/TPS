cls
@echo off

REM === Formation : ESIR1, matiere : SYS
 set RepForm=esir1
 set RepDef=sys

REM === parametre ?
 if G:%1==G: goto paramdefaut
 set RepMat=%1
 goto debut0

:paramdefaut
 set RepMat=%RepDef%

:debut0
 if exist H:\%RepMat%  goto debut1
 echo --
 echo -- ***** le repertoire %RepMat% n'existe pas sur H: *****
 echo -- Il va etre cree
 echo --
 echo --
 echo -- pour un autre choix, annuler la commande (controle+C)
 echo --    et recommencer en le specifiant en parametre
 echo --    exemple :   %RepDef%  TpIsys   (attention nom DOS: 8 car max, pas d'espace)
 echo --
 echo --
 pause
 cls

 md H:\%RepMat%  
 goto debut2

:debut1
 echo --
 echo -- le repertoire par defaut sur H: sera %RepMat%
 echo --
 echo --
 echo -- pour un autre choix, annuler la commande (controle+C)
 echo --    et recommencer en le specifiant en parametre
 echo --    exemple :   %RepDef%  TpIsys   (attention nom DOS: 8 car max, pas d'espace)
 echo --
 echo --
 pause
 cls


:debut2
echo  ***** Mise en place de l'environnement pour %RepMat% *****
echo  . 
echo  . 

REM ===== Repertoire par défaut sur G: =====

cd G:\
set RepG=G:\
If exist G:\%RepForm% Set repG=G:\%RepForm%
If exist G:\%RepForm%  cd G:\%RepForm%
If exist G:%RepDef% Set repG=%RepG%\%RepDef%
If exist G:%RepDef% cd G:%RepDef%

REM ===== creation c:\temp\%username%  =====

if exist c:\temp\%username%  goto suite0
md c:\temp\%username%  >c:\temp\nul
echo  ***      creation de C:\Temp\%username%

REM ===== creation c:\temp\%username%\%RepMat%  =====

:suite0
if exist c:\temp\%username%\%RepMat% goto suite1
md c:\temp\%username%\%RepMat%   >c:\temp\nul
echo  ***      creation de C:\Temp\%username%\%RepMat%

:suite1
c:
cd c:\temp\%username%\%RepMat% >c:\temp\nul
set RepCour= c:\temp\%username%\%RepMat%

REM ===== Repertoire sur H:  =====

if exist h:\%RepMat% goto suite2
rem echo  ***
rem echo  ***      Le repertoire H:\%RepMat% n'existe pas
set RepH=H:\
cd H:\
goto suite3

:suite2
 echo  ***      copie de l'arborescence H:\%RepMat% dans le repertoire de travail  
 xcopy h:\%RepMat% /e /y >nul
 set RepH=H:\%RepMat%

:suite3
 cd %RepH%
 echo  .
 echo  .
 echo  .
 echo  ***      
 echo  ***      Repertoire de travail : C:\Temp\%username%\%RepMat% 
 echo  ***      
 echo  ***      
 echo  ***      Repertoires par defaut :  
 echo  ***      
 echo  ***        %RepH%
 echo  ***        %RepG%
 echo  ***      
 echo  ***      

REM ===== Extension des regles de recherche =====
kb16 fr
if exist c:\progra~1\tasm path= c:\progra~1\tasm;%path%   > c:\temp\nul
if exist g:\%RepForm%\tasm path= g:\%RepForm%\tasm;%path%   > c:\temp\nul
path= g:\%RepForm%\%RepMat%;%path%   > c:\temp\nul
doskey
