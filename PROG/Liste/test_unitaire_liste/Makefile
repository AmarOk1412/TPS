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

all : test_liste

test_liste : main_test.o test_unitaire_p1_base.o test_unitaire_p2_iterator.o test_unitaire_p4.o test_unitaire_p3a_find_insert_erase.o test_unitaire_p3b_recherche_copie.o
	$(CXX) $(LDFLAGS) -lpthread $^ $(LIBS) -o $@

test : test_liste
	./test_liste < donnees_liste > test.sor

raz clean :
	-rm *.o *~ test_vecteur test_vecteur_valgrind
