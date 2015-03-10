# root of Google Test
GTEST_DIR = ./OUTILS/google_test

# Flags passed to the preprocessor.
CPPFLAGS += -I$(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -fno-elide-constructors

# libs to link statically
LIBS  =  $(GTEST_DIR)/lib/.libs/libgtest.a

%.o : %.cc %.hh
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $*.o

%.o : %.cpp %.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $*.o

test_vecteur_valgrind.o : test_vecteur.cc
	$(CXX) $(CPPFLAGS) -DVALGRIND $(CXXFLAGS) -c $< -o $*.o

all : test_vecteur test_vecteur_valgrind

test_vecteur : test_vecteur.o vecteur.o 
	$(CXX) $(LDFLAGS) -lpthread $^ $(LIBS) -o $@

test_vecteur_valgrind : test_vecteur_valgrind.o vecteur.o
	$(CXX) $(LDFLAGS) -lpthread $^ $(LIBS) -o $@

test : test_vecteur
	./test_vecteur < donnees_test > test.sor
	valgrind ./test_vecteur_valgrind < donnees_test > /dev/null 2> valgrind.sor

raz clean :
	-rm *.o *~ test_vecteur test_vecteur_valgrind
