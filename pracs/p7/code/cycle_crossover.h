#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

const int CYCLE_START = 0;

void cycle_crossover(std::vector<int> initial_population[], std::vector<int> new_population[]);
std::unordered_set<int> get_cycle(std::vector<int> &p1, std::vector<int> &p2);
int get_position(int value, std::vector<int> &v);
void print_individual(std::unordered_set<int> &s); 
void remove_elements_cycle(std::unordered_set<int> &cycle, std::vector<int> &v, bool in_cycle);