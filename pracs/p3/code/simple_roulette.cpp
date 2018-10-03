#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;
const int POPULATION_SIZE = 32;
const int MAX_INDIVIDUAL_SIZE = 31;
const int MIN_INDIVIDUAL_SIZE = 0;
const int POPULATION_BITS = 5;
const int MUTATION_PROBABILITY = 10;
const int CROSS_POS = 4;

unsigned int get_value(bitset<POPULATION_BITS>& p) {
    return (unsigned int)(p.to_ulong());
}

unsigned int calculate_aptitude(unsigned int value) {
    return (unsigned int)pow(value, 2);
}

bitset<POPULATION_BITS> roulette_selection(bitset<POPULATION_BITS> population[], unsigned int total) {
    float r = rand() % (total + 1);
    unsigned int sum = 0;
    int i;
    for(i=0; i < POPULATION_SIZE && sum < r; i++) {
        // Evaluation
        unsigned int value = get_value(population[i]);
        unsigned int aptitude = calculate_aptitude(value);
        sum += aptitude;
    }
    return population[i];
}

bitset<POPULATION_BITS> cross(bitset<POPULATION_BITS> &p1, bitset<POPULATION_BITS> &p2, 
    int cross_point) {
    bitset<POPULATION_BITS> child = p1;
    child.set(cross_point, p2[cross_point]);
    return child;
}

bool has_mutation(unsigned int mutations[], int num_individual, unsigned int num_mutations){
    for (int i = 0; i < num_mutations; i++) {
        if (mutations[i] == num_individual) {
            return true;
        }
    }
    return false;
}

bitset<POPULATION_BITS> mutate(bitset<POPULATION_BITS> individual) {
    bitset<POPULATION_BITS> mutated_individual = individual;
    for (int i = 0; i < individual.size(); i++) {
        bool value = rand() % (2);
        if (value == false) {
            continue;
        } else {
            mutated_individual.set(i, value);
        }
    }
    return mutated_individual;
}

int main(int argc, char *argv[]) {
    srand(time(0));
	bitset<POPULATION_BITS> initial_population[POPULATION_SIZE];
    bitset<POPULATION_BITS> descendancy[POPULATION_SIZE];
    unsigned int total = 0;

    // Initialization, evaluation
    for (int i = 0; i < POPULATION_SIZE; i++) {
        unsigned int random_value = rand() % (MAX_INDIVIDUAL_SIZE - MIN_INDIVIDUAL_SIZE + 1) 
        + MIN_INDIVIDUAL_SIZE;
        // Init
        initial_population[i] = bitset<POPULATION_BITS>(random_value);
        // Evaluation
        unsigned int value = get_value(initial_population[i]);
        unsigned int aptitude = calculate_aptitude(value);
        total += aptitude; 
    }

    for (int j = 0; j < 10; j++) {
        // Parent Selection
        for (int i = 0; i < POPULATION_SIZE; i++) {
            descendancy[i] = roulette_selection(initial_population, total);
        }

        // Next Generation
        for (int i = 0; i < POPULATION_SIZE; i++) {
            initial_population[i] = descendancy[i];
        }

        // Cross and Mutation
        // Mutar aleatoriamente el individuo
        unsigned int num_indiv_mutar = POPULATION_SIZE / MUTATION_PROBABILITY;
        unsigned int mutations[num_indiv_mutar];
        total = 0;
        for (int i = 0; i < num_indiv_mutar; i++) {
            mutations[i] = rand() % (POPULATION_SIZE + 1);
        }
        for (int i = 0; i < POPULATION_SIZE; i+=2) {
            // Cross
            descendancy[i] = cross(initial_population[i], initial_population[i + 1], CROSS_POS);
            descendancy[i + 1] = cross(initial_population[i + 1], initial_population[i], CROSS_POS);
            // cout << initial_population[i] << ":" << initial_population[i].to_ulong()
            //  << " - " << descendancy[i] 
            // << ":" <<descendancy[i].to_ulong() << endl;
            // cout << initial_population[i+1] << ":" << initial_population[i + 1].to_ulong() << " - " << descendancy[i + 1] 
            // << ":" <<descendancy[i + 1].to_ulong() << endl << endl;
            // Mutation
            if (has_mutation(mutations, i, num_indiv_mutar)) {
                descendancy[i] = mutate(descendancy[i]);
            }
            if (has_mutation(mutations, i + 1, num_indiv_mutar)) {
                descendancy[i + 1] = mutate(descendancy[i + 1]);
            }
            // Evaluation
            unsigned int value1 = get_value(descendancy[i]);
            unsigned int value2 = get_value(descendancy[i + 1]);
            unsigned int aptitude1 = calculate_aptitude(value1);
            unsigned int aptitude2 = calculate_aptitude(value2);
            total += aptitude1 + aptitude2; 
        }
        
        // Next Generation
        for (int i = 0; i < POPULATION_SIZE; i++) {
            initial_population[i] = descendancy[i];
            cout << descendancy[i] << endl;
        }
        cout << endl << endl;
    }
    return 0;
}
