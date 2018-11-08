#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include "crosses.h"
#include "order_crossover.h"
#include "partially_mapped_crossover.h"
#include "position_based_crossover.h"
#include "order_based_crossover.h"
#include "cycle_crossover.h"

void initialize_population(std::vector<int> initial_population[]);

int main(int argc, char *argv[]) { 
    srand(time(0));
    std::vector<int> initial_population[POPULATION_SIZE];
    std::vector<int> crossed_population[POPULATION_SIZE];
    int op;
    std::cout << "Ingrese el algoritmo a usar:" << std::endl;
    std::cout << "1.- ORDER-CROSSOVER" << std::endl;
    std::cout << "2.- PARTIALLY MAPPED CROSSOVER" << std::endl;
    std::cout << "3.- POSITION BASED CROSSOVER" << std::endl;
    std::cout << "4.- ORDER BASED CROSSOVER" << std::endl;
    std::cout << "5.- CYCLE CROSSOVER" << std::endl;
    scanf("%d", &op);
    // Init
    initialize_population(initial_population);
    switch(op) {
        case 1:
            std::cout << std::endl << "ORDER CROSS-OVER" << std::endl << std::endl;
            order_cross_over(initial_population, crossed_population);
        break;
        case 2:
            std::cout << std::endl << "PARTIALLY MAPPED CROSS-OVER" << std::endl << std::endl;
            partially_mapped_crossover(initial_population, crossed_population);
        break;
        case 3:
            std::cout << std::endl << "POSITION BASED CROSS-OVER" << std::endl << std::endl;
            position_based_crossover(initial_population, crossed_population);
        break;
        case 4:
            std::cout << std::endl << "ORDER BASED CROSS-OVER" << std::endl << std::endl;
            order_based_crossover(initial_population, crossed_population);
        break;
        case 5:
            std::cout << std::endl << "CYCLE CROSS-OVER" << std::endl << std::endl;
            cycle_crossover(initial_population, crossed_population);
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

