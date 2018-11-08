#include "cycle_crossover.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include "crosses.h"

int get_position(int value, std::vector<int> &v) {
    for (int i=0; i < INDIVIDUAL_ELEMENTS; i++) {
        if (value == v[i]) {
            return i;
        }
    }
    return 0;
}

void print_individual(std::unordered_set<int> &s) {
    for (const auto& elem : s) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

std::unordered_set<int> get_cycle(std::vector<int> &p1, std::vector<int> &p2) {
    std::unordered_set<int> cycle;
    std::unordered_set<int> positions;
    bool has_another_cycle = true;
    int pos1 = CYCLE_START;
    int pos2 = CYCLE_START;
    int elem1 = p1[CYCLE_START];
    int elem2 = p2[CYCLE_START];
    // Add the first element to the cycle
    positions.insert(CYCLE_START);
    cycle.insert(elem1);
    cycle.insert(elem2);
    int i = 0;
    while (has_another_cycle) {
        bool error1 = false;
        bool error2 = false;
        // if we don't have the position, add it and it's element
        pos1 = get_position(elem2, p1);
        if (positions.find(pos1) == positions.end()) {
            positions.insert(pos1);
            cycle.insert(p1[pos2]);
        } else {
            error1 = true;
        }
        pos2 = get_position(elem1, p2);
        if (positions.find(pos2) == positions.end()) {
            positions.insert(pos2);
            cycle.insert(p2[pos1]);
        } else {
            error2 = true;
        }
        if (error1 && error2) {
            has_another_cycle = false;
            break;
        }
        elem1 = p1[pos2];
        elem2 = p2[pos1];
        i++;
        if (i >= 4) {
            has_another_cycle = false;
            break;
        }

    }
    return cycle;
}

void remove_elements_cycle(std::unordered_set<int> &cycle, std::vector<int> &v, bool in_cycle) {
    if (in_cycle) {
        for (auto& elem : v) {
            if(cycle.find(elem) != cycle.end()) {
                v.erase(remove(v.begin(), v.end(), elem), v.end());
            }
        }
        for (auto& elem : v) {
            if(cycle.find(elem) != cycle.end()) {
                v.erase(remove(v.begin(), v.end(), elem), v.end());
            }
        }
    } else {
        for (auto& elem : v) {
            if(cycle.find(elem) == cycle.end()) {
               elem = 0;
            }
        }
    }
}

void cycle_crossover(std::vector<int> initial_population[], std::vector<int> new_population[]) {
    for (int i = 0 ; i < POPULATION_SIZE; i+=2) {
        std::vector<int> p1 = initial_population[i];
        std::vector<int> p2 = initial_population[i + 1];
        std::cout << "P1: ";
        print_individual(p1);
        std::cout << "P2: ";
        print_individual(p2);
        // Construct the cycle
        std::unordered_set<int> cycle = get_cycle(initial_population[0], initial_population[1]);
        std::cout << "Cycle: ";
        print_individual(cycle);  
        //h1     
        std::vector<int> h1 = p1;
        // Remove the elements that are different from the ones in the cycle
        remove_elements_cycle(cycle, h1, false);
        std::cout << "H1: ";
        print_individual(h1);
        std::vector<int> p2_prime = p2;
        // Remove the elements of the cycle
        remove_elements_cycle(cycle, p2_prime, true);
        std::cout << "P2': ";
        print_individual(p2_prime);
        // substitute the 0's in h1 from p2'
        for (int j = 0, k = 0; j < INDIVIDUAL_ELEMENTS; j++) {
            if (h1[j] == 0) {
                h1[j] = p2_prime[k];
                k++;
            }
        }
        std::cout << "H1: ";
        print_individual(h1);
        //h2 
        std::vector<int> h2 = p2;
        // Remove the elements that are different from the ones in the cycle
        remove_elements_cycle(cycle, h2, false);
        std::cout << "H2: ";
        print_individual(h2);
        std::vector<int> p1_prime = p1;
        // Remove the elements of the cycle
        remove_elements_cycle(cycle, p1_prime, true);
        std::cout << "P1': ";
        print_individual(p1_prime);
        // substitute the 0's in h2 from p1'
        for (int j = 0, k = 0; j < INDIVIDUAL_ELEMENTS; j++) {
            if (h2[j] == 0) {
                h2[j] = p1_prime[k];
                k++;
            }
        }
        std::cout << "H2: ";
        print_individual(h2);
        std::cout << std::endl;
    }
}
