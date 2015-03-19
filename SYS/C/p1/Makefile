# petit tutoriel : http://perso.univ-rennes1.fr/jean-christophe.engel/make

#------------------------------------------------------------------------
# les variables
#------------------------------------------------------------------------

# compilateur C
CC	 = gcc

# options de compilation
CFLAGS   = -ggdb -export-dynamic -Wall -fPIC -shared -std=c99

# options d'édition de liens
LDFLAGS  = 

# les programmes exécutables à fabriquer (à compléter)
PROGS	= ptrfn_v1 ptrfn_v2 dynload_v1 dynload_v2 afficher.o libcalcul.so libcalcul2.so main_calcul

all : $(PROGS)

# 1. ptrfn_v1 et ptrfn_v2 : règles implicites

# 2. utiliser une bibliothèque chargée dynamiquement (libm.so)
dynload_v1 : dynload_v1.o
	$(CC) $(LDFLAGS) -o $@ $< -ldl
	
dynload_v2 : dynload_v2.o
	$(CC) $(LDFLAGS) -o $@ $< -ldl

# 3. fabriquer une bibliothèque chargée dynamiquement
calcul.o : calcul.c
	$(CC) -c $(CFLAGS) -fPIC $< -o $@

afficher.o : afficher.h
	$(CC) -c $(CFLAGS) -fPIC $< -o $@

libcalcul.so : calcul.o
	$(CC) -shared -export-dynamic -fPIC -o $@ $<
	
libcalcul2.so : calcul2.o
	$(CC) -fPIC -export-dynamic -shared -o $@ $<

main_calcul : main_calcul.o
	$(CC) $(LDFLAGS) -export-dynamic -o $@ $< -ldl

# divers
.PHONY : clean

clean:
	-@rm *.o *~ $(PROGS)
