#include "insertion_mutation.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include "crosses.h"


void insertion_mutation(std::vector<int> initial_population[], std::vector<int> new_population[]) {
    for (int i = 0 ; i < POPULATION_SIZE; i++) {
        std::vector<int> p = initial_population[i];
        std::cout << "P: ";
        print_individual(p);
        int pos_1 = random() % (INDIVIDUAL_ELEMENTS); 
        int pos_2 = random() % (INDIVIDUAL_ELEMENTS);
        // Insert the element
        p.insert (p.begin() + pos_1, p.begin(), p.end());
        std::cout << "P: ";
        print_individual(p);
        new_population[i] = p;
        std::cout << std::endl;
    }
}
