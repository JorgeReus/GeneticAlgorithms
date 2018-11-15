#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include "crosses.h"
#include "insertion_mutation.h"
#include "displacement_mutation.h"
#include "reciprocal_mutation.h"
#include "heuristic_mutation.h"

void initialize_population(std::vector<int> initial_population[]);

int main(int argc, char *argv[]) { 
    srand(time(0));
    std::vector<int> initial_population[POPULATION_SIZE];
    std::vector<int> crossed_population[POPULATION_SIZE];
    int op;
    std::cout << "Ingrese el algoritmo a usar:" << std::endl;
    std::cout << "1.- INSERTION MUTATION" << std::endl;
    std::cout << "2.- DISPLACEMENT MUTATION" << std::endl;
    std::cout << "3.- RECIPROCAL INTERCHANGE MUTATION" << std::endl;
    std::cout << "4.- HEURISTIC MUTATION" << std::endl;
    scanf("%d", &op);
    // Init
    initialize_population(initial_population);
    switch(op) {
        case 1:
            std::cout << std::endl << "INSERTION MUTATION" << std::endl << std::endl;
            insertion_mutation(initial_population, crossed_population);
        break;
        case 2:
            std::cout << std::endl << "DISPLACEMENT MUTATION" << std::endl << std::endl;
            displacement_mutation(initial_population, crossed_population);
        break;
        case 3:
            std::cout << std::endl << "RECIPROCAL INTERCHANGE MUTATION" << std::endl << std::endl;
            reciprocal_mutation(initial_population, crossed_population);
        break;
        case 4:
            std::cout << std::endl << "HEURISTIC MUTATION" << std::endl << std::endl;
            heuristic_mutation(initial_population, crossed_population);
        break;
        default:
        std::cout << "Opción inválida" << std::endl;
    }
    return 0;
}

void initialize_population(std::vector<int> initial_population[]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        // Create the individual
        std::vector<int> individual;
        // Insert random elements between MAX_INDIVIDUAL_SIZE and MIN_INDIVIDUAL_SIZE
        std::unordered_set<int> values;
        for (int j = 0; j < INDIVIDUAL_ELEMENTS; j++) {
            int random_value = rand() % (MAX_INDIVIDUAL_SIZE - MIN_INDIVIDUAL_SIZE + 1) + MIN_INDIVIDUAL_SIZE;
            while(values.find(random_value) != values.end()) {
                random_value = rand() % (MAX_INDIVIDUAL_SIZE - MIN_INDIVIDUAL_SIZE + 1) + MIN_INDIVIDUAL_SIZE;
            }
            values.insert(random_value);
            individual.push_back(random_value);
        }
        initial_population[i] = individual;
    }
}

