#include "crosses.h"
#include <vector>
#include <map>
#include <iostream>

void print_individual(std::vector<int> &individual) {
    for (int i : individual) {
        if (i == 0) {
            std::cout << "X ";
        } else {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

std::vector<int> random_string(std::vector<int> p1) {
    std::map<int, int> r_values;
    int string_size = random() % (INDIVIDUAL_ELEMENTS - 1) + 1;
    std::vector<int> child = std::vector<int>(p1.size());
    for (int i = 0 ; i < string_size; i++) {
        int value = random() % (INDIVIDUAL_ELEMENTS - 1) + 1;
        r_values[value] = p1[value]; 
    }
    for (auto& kv : r_values) {
        child[kv.first] = kv.second;
    }
    return child;
}