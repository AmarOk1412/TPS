#------------------------------------------------------------------------
# les variables
#------------------------------------------------------------------------

# fichiers d'entête openCV pour compilation
INC	 = `pkg-config --cflags opencv`

# bibliothèques openCV pour édition de liens
LIBS	 = `pkg-config --libs opencv`

# compilateur C++
CXX	 = g++

# options de compilation
CXXFLAGS = -c -Wall -ggdb $(INC) -I../include

# options d'édition de liens
LDFLAGS  = $(LIBS) -ldl

# tous les fichiers source C++ du répertoire courant
SRC1	 = $(wildcard *.cc)
SRC2	 = $(wildcard *.cpp)

# les fichiers objet correspondant
OBJ	 = $(patsubst %.cc,../bin/%.o,$(SRC1)) $(patsubst %.cpp,../bin/%.o,$(SRC2))

# le nom du programme exécutable
EXEC	 = ../bin/imagesystem

#------------------------------------------------------------------------
# les règles d'action (compilation, édition de liens, ...)
#------------------------------------------------------------------------

all : $(EXEC)

# compilation : produire un objet à partir d'un source
../bin/%.o : %.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@

# idem
../bin/%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# édition de liens : produire l'exécutable à partir des objets
$(EXEC) : $(OBJ)
	$(CXX) $(LDFLAGS) -export-dynamic $^ -o $@

# un peu de nettoyage
clean :
	-@rm -f *~ ../bin/*.o $(EXEC)
