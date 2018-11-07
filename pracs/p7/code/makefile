crosses: crosses.cpp functions.cpp order_crossover.o partially_mapped_crossover.o position_based_crossover.o order_based_crossover.o cycle_crossover.o
	g++ crosses.cpp functions.cpp order_crossover.o partially_mapped_crossover.o position_based_crossover.o order_based_crossover.o cycle_crossover.o -o crosses -std=c++11
order_crossover.o: order_crossover.cpp order_crossover.h
	g++ -c order_crossover.cpp -std=c++11
partially_mapped_crossover.o: partially_mapped_crossover.cpp partially_mapped_crossover.h
	g++ -c partially_mapped_crossover.cpp -std=c++11
position_based_crossover.o: position_based_crossover.cpp position_based_crossover.h
	g++ -c position_based_crossover.cpp -std=c++11
order_based_crossover.o: order_based_crossover.cpp order_based_crossover.h
	g++ -c order_based_crossover.cpp -std=c++11
cycle_crossover.o: cycle_crossover.cpp cycle_crossover.h
	g++ -c cycle_crossover.cpp -std=c++11