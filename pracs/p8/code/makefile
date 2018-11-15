mutations: mutations.cpp functions.cpp insertion_mutation.o displacement_mutation.o reciprocal_mutation.o heuristic_mutation.o
	g++ mutations.cpp functions.cpp insertion_mutation.o displacement_mutation.o reciprocal_mutation.o heuristic_mutation.o -o mutations -std=c++11
insertion_mutation.o: insertion_mutation.cpp insertion_mutation.h
	g++ -c insertion_mutation.cpp -std=c++11
displacement_mutation.o: displacement_mutation.cpp displacement_mutation.h
	g++ -c displacement_mutation.cpp -std=c++11
reciprocal_mutation.o: reciprocal_mutation.cpp reciprocal_mutation.h
	g++ -c reciprocal_mutation.cpp -std=c++11
heuristic_mutation.o: heuristic_mutation.cpp heuristic_mutation.h
	g++ -c heuristic_mutation.cpp -std=c++11	
