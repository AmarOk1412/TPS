# fichiers d'entête openCV pour compilation
INC  = `pkg-config --cflags opencv`

# bibliothèques openCV pour édition de liens
LIBS = `pkg-config --libs opencv`

# compilateur C++
CXX	 = g++

# options de compilation
CXXFLAGS = -Wall -ggdb $(INC) -I../include -fPIC

# options d'édition de liens
LDFLAGS	 = -shared

# tous les fichiers source C++ du répertoire courant
SRC1	 = $(wildcard *.cc)
SRC2	 = $(wildcard *.cpp)
LIBS	 = $(patsubst %.cc,%.so,$(SRC1)) $(patsubst %.cpp,%.so,$(SRC2))

all : $(LIBS)

# produire une bibliothèque dynamique à partir d'un objet
%.so : %.o
	$(CXX) $(LDFLAGS) -o $@ $<

clean : 
	-@rm *~ *.so
