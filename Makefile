
CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++11

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

main: main.o aireDeJeu.o joueur.o unite.o fantassin.o archer.o catapulte.o superSoldat.o
	$(CXX) $^ -o $@

.PHONY: run clean

run: main
	./$<

clean:
	rm -f *.o *~ main