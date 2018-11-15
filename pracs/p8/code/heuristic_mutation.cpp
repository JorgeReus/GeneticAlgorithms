#include "heuristic_mutation.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include "crosses.h"

int factorial(int n)
{
    int ret = 1;
    for(int i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}

std::vector<int> get_permutation(std::vector<int> v) {
    std::vector<int> p;
    std::vector<int> aux = v;
    // Calculate permutations
    for (int i=0; i < labmda; i++) {
        int r_pos = random() % (INDIVIDUAL_ELEMENTS);
        do {    
            r_pos = random() % (INDIVIDUAL_ELEMENTS);
        }
        while(std::find(p.begin(), p.end(), v[r_pos]) != p.end());
        p.push_back(v[r_pos]);
        aux[r_pos] = 0;
    }
    int num_perms = factorial(labmda);
    std::vector<int> permutations[num_perms];
    std::sort(p.begin(), p.end());
    int i=0;
    do {
        permutations[i] = p;
        i++;
    } while(std::next_permutation(p.begin(), p.end()));
    std::vector<int> result = permutations[random() % (num_perms)];
    for (int j=0, k=0; j < INDIVIDUAL_ELEMENTS; j++) {
        if(aux[j] == 0) {
            aux[j] = result[k];
            k++;
        }
    }
    return aux;
}

void heuristic_mutation(std::vector<int> initial_population[], std::vector<int> new_population[]) {
    for (int i = 0 ; i < POPULATION_SIZE; i++) {
        std::vector<int> p = initial_population[i];
        std::cout << "P: ";
        print_individual(p);
        std::vector<int> permutation = get_permutation(p);
        std::cout << "P: ";
        print_individual(permutation);
        std::cout << std::endl;
    }
}
