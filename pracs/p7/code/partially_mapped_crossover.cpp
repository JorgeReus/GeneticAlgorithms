#include "partially_mapped_crossover.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include "crosses.h"


void partially_mapped_crossover(std::vector<int> initial_population[], 
std::vector<int> new_population[]) {
    int segment_size = INDIVIDUAL_ELEMENTS / 3;
    for (int i = 0; i < POPULATION_SIZE; i+=2) {
        std::vector<int> p1 = initial_population[i];
        std::vector<int> p2 = initial_population[i + 1];
        std::vector<int> h1 = std::vector<int>(INDIVIDUAL_ELEMENTS);
        std::vector<int> h2 = std::vector<int>(INDIVIDUAL_ELEMENTS);
        std::unordered_set<int> h1_values;
        std::unordered_set<int> h2_values;
        for (int j = segment_size; j < segment_size * 2; j++) {
            h1[j] = p2[j];
            h2[j] = p1[j];
            h1_values.insert(p2[j]);
            h2_values.insert(p1[j]);
        }
        std::cout << "P1: ";
        print_individual(p1);
        std::cout << "P2: ";
        print_individual(p2);
        std::cout << "H1: ";
        print_individual(h1);
        std::cout << "H2: ";
        print_individual(h2);
        // copy the values that arent int the copied segment
        for (int j = 0; j < segment_size; j++) {
            if (h1_values.find(p1[j]) == h1_values.end()) {
               h1[j] = p1[j]; 
            } 
            if (h2_values.find(p2[j]) == h2_values.end()) {
               h2[j] = p2[j]; 
            } 
        }
        for (int j = segment_size * 2; j < INDIVIDUAL_ELEMENTS; j++) {
            if (h1_values.find(p1[j]) == h1_values.end()) {
               h1[j] = p1[j]; 
            } 
            if (h2_values.find(p2[j]) == h2_values.end()) {
               h2[j] = p2[j]; 
            }
        }
        // Map the rest of the values
        std::unordered_set<int>::iterator itr_1 = h1_values.begin();
        std::unordered_set<int>::iterator itr_2 = h2_values.begin();
        for (int j = 0; j < INDIVIDUAL_ELEMENTS; j++) {
            if (h1[j] == 0) {
                while (h1_values.find(*itr_2) != h1_values.end()) {
                    itr_2++;
                }
                h1[j] = *itr_2;
                itr_2++; 
            }
            if (h2[j] == 0) {
                while (h2_values.find(*itr_1) != h2_values.end()) {
                    itr_1++;
                }
                h2[j] = *itr_1;
                itr_1++; 
            }
        }
        std::cout << "H1: ";
        print_individual(h1);
        std::cout << "H2: ";
        print_individual(h2);
        std::cout << std::endl;
    }
}
