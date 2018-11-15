#include "displacement_mutation.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include "crosses.h"

void displacement_mutation(std::vector<int> initial_population[], std::vector<int> new_population[]) {
    for (int i = 0 ; i < POPULATION_SIZE; i++) {
        std::vector<int> p = initial_population[i];
        int num_elements = random() % (INDIVIDUAL_ELEMENTS / 2);
        std::unordered_set<int> initial_positions;
        std::unordered_set<int> end_positions;
        std::cout << num_elements << " random elements" << std::endl;
        std::cout << "P: ";
        print_individual(p);
        for (int j = 0; j < num_elements; j++) {
            int initial_pos;
            int end_pos;
            // While the element already exists calculate a new one
            do {
                initial_pos = random() % (INDIVIDUAL_ELEMENTS);
                end_pos = random() % (INDIVIDUAL_ELEMENTS);
            }
            while (
                (initial_positions.find(initial_pos) != initial_positions.end()) && (end_positions.find(end_pos) != end_positions.end())
                );
            initial_positions.insert(initial_pos);
            end_positions.insert(end_pos);
            // Swap the elements
            std::iter_swap(p.begin() + initial_pos, p.begin() + end_pos);
        }
        std::cout << "P: ";
        print_individual(p);
        new_population[i] = p;
        std::cout << std::endl;
    }
}
