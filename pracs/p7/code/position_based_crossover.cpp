#include "position_based_crossover.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include "crosses.h"


void position_based_crossover(std::vector<int> initial_population[], std::vector<int> new_population[]) {
    
    for (int i = 0 ; i < POPULATION_SIZE; i+=2) {
        std::vector<int> p1 = initial_population[i];
        std::vector<int> p2 = initial_population[i + 1];
        std::cout << "P1: ";
        print_individual(p1);
        // Get the substring for h1
        std::vector<int> h1 = random_string(p1);
        std::cout << "H1: ";
        print_individual(h1);
        std::vector<int> p2_prime = p2;
        // Erase the elemets of h1 from p2
        for (int j = 0; j < INDIVIDUAL_ELEMENTS; j++) {
            p2_prime.erase(remove(p2_prime.begin(), p2_prime.end(), h1[j]), p2_prime.end());
        }
        // substitute the 0's in h1 from p2'
        for (int j = 0, k = 0; j < INDIVIDUAL_ELEMENTS; j++) {
            if (h1[j] == 0) {
                h1[j] = p2_prime[k];
                k++;
            }
        }
        std::cout << "P2': ";
        print_individual(p2_prime);
        std::cout << "H1: ";
        print_individual(h1);
        std::cout <<std::endl;
        // Get the substring for h2
        std::cout << "P2: ";
        print_individual(p2);
        std::vector<int> h2 = random_string(p2);
        std::cout << "H2: ";
        print_individual(h2);
        std::vector<int> p1_prime = p1;
        // Erase the elemets of h2 from p1
        for (int j = 0; j < INDIVIDUAL_ELEMENTS; j++) {
            p1_prime.erase(std::remove(p1_prime.begin(), p1_prime.end(), h2[j]), p1_prime.end());
        }
        // substitute the 0's in h1 from p2'
        for (int j = 0, k = 0; j < INDIVIDUAL_ELEMENTS; j++) {
            if (h2[j] == 0) {
                h2[j] = p1_prime[k];
                k++;
            }
        }
        std::cout << "P1': ";
        print_individual(p1_prime);
        std::cout << "H2: ";
        print_individual(h2);
        std::cout << std::endl;
    }
}
