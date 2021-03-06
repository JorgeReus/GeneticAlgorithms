#include "reciprocal_mutation.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include "crosses.h"


void reciprocal_mutation(std::vector<int> initial_population[], std::vector<int> new_population[]) {
    for (int i = 0 ; i < POPULATION_SIZE; i++) {
        std::vector<int> p = initial_population[i];
        std::cout << "P: ";
        print_individual(p);
        int pos_1 = random() % (INDIVIDUAL_ELEMENTS); 
        int pos_2 = random() % (INDIVIDUAL_ELEMENTS);
        // Swap the elements
        std::iter_swap(p.begin() + pos_1, p.begin() + pos_2);
        std::cout << "P: ";
        print_individual(p);
        new_population[i] = p;
        std::cout << std::endl;
    }
}
