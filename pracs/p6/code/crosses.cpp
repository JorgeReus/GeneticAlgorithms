#include <cmath>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <locale>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <bits/stdc++.h>

using namespace std;

const int POPULATION_SIZE = 32;
const int MAX_INDIVIDUAL_SIZE = 31;
const int MIN_INDIVIDUAL_SIZE = 0;
const int POPULATION_BITS = 5;
const int MAX_CROSS_POINT = 4;
const int MIN_CROSS_POINT = 1;

void single_point_cross(bitset<POPULATION_BITS> initial_population[], 
bitset<POPULATION_BITS> new_population[]);
void double_point_cross(bitset<POPULATION_BITS> initial_population[], 
bitset<POPULATION_BITS> new_population[]);
void uniform_cross(bitset<POPULATION_BITS> initial_population[], 
bitset<POPULATION_BITS> new_population[]);
void accented_crossing(bitset<POPULATION_BITS> initial_population[], 
bitset<POPULATION_BITS> new_population[]);

int main(int argc, char *argv[]) { 
    srand(time(0));
    bitset<POPULATION_BITS> initial_population[POPULATION_SIZE];
    bitset<POPULATION_BITS> crossed_population[POPULATION_SIZE];

    for (int i = 0; i < POPULATION_SIZE; i++) {
        int random_value = rand() % (MAX_INDIVIDUAL_SIZE - MIN_INDIVIDUAL_SIZE + 1) 
        + MIN_INDIVIDUAL_SIZE;
        // Init
        initial_population[i] = bitset<POPULATION_BITS>(random_value);
    }
    cout << endl << "SINGLE POINT CROSSING" << endl << endl;
    single_point_cross(initial_population, crossed_population);
    cout << endl << "DOUBLE POINT CROSSING" << endl << endl;
    double_point_cross(initial_population, crossed_population);
    cout << endl << "UNIFORM CROSSING" << endl << endl;
    uniform_cross(initial_population, crossed_population);
    cout << endl <<  "ACCENTED CROSSING" << endl << endl;
    accented_crossing(initial_population, crossed_population);

    return 0;
}

void single_point_cross(bitset<POPULATION_BITS> initial_population[], 
bitset<POPULATION_BITS> new_population[]) {
    for (int i = 0 ; i < POPULATION_SIZE; i+=2) {
        // Cross point
        int random_pos = rand() % (MAX_CROSS_POINT - MIN_CROSS_POINT + 1) 
            + MIN_CROSS_POINT;
        bitset<POPULATION_BITS> child1 = initial_population[i];
        bitset<POPULATION_BITS> child2 = initial_population[i + 1];
        // Crossing from right to left
        for (int j = 0; j < POPULATION_BITS; j++) {
            if (j < random_pos) {
                child1[j] = initial_population[i][j]; 
                child2[j] = initial_population[i + 1][j]; 
            } else {
                child1[j] = initial_population[i + 1][j]; 
                child2[j] = initial_population[i][j]; 
            }
        }
        new_population[i] = child1;
        new_population[i + 1] = child2;
        cout << "Cross Point: " << random_pos << endl;
        cout << initial_population[i] << " x " << initial_population[i + 1] << " : " << endl; 
        cout << child1 << " and " << child2 << endl; 
    }
}

void double_point_cross(bitset<POPULATION_BITS> initial_population[], 
bitset<POPULATION_BITS> new_population[]) {
    for (int i = 0 ; i < POPULATION_SIZE; i+=2) {
        // Cross points
        int random_pos1 = rand() % (MAX_CROSS_POINT - MIN_CROSS_POINT + 1) 
            + MIN_CROSS_POINT;
        int random_pos2;
        while ((random_pos2 = rand() % (MAX_CROSS_POINT - MIN_CROSS_POINT + 1)  + MIN_CROSS_POINT) == random_pos1);  
        bitset<POPULATION_BITS> child1 = initial_population[i];
        bitset<POPULATION_BITS> child2 = initial_population[i + 1];
        // Crossing from right to left
        for (int j = 0; j < POPULATION_BITS; j++) {
            if (j < random_pos1) {
                child1[j] = initial_population[i][j]; 
                child2[j] = initial_population[i + 1][j]; 
            } else if (j >= random_pos1 && j < random_pos2) {
                child1[j] = initial_population[i + 1][j]; 
                child2[j] = initial_population[i][j]; 
            } else {
                child1[j] = initial_population[i][j]; 
                child2[j] = initial_population[i + 1][j]; 
            }
        }
        new_population[i] = child1;
        new_population[i + 1] = child2;
        cout << "Cross Points: " << random_pos1 << " " << random_pos2 <<endl;
        cout << initial_population[i] << " x " << initial_population[i + 1] << " : " << endl; 
        cout << child1 << " and " << child2 << endl; 
    }
}


void uniform_cross(bitset<POPULATION_BITS> initial_population[], 
bitset<POPULATION_BITS> new_population[]) {
    for (int i = 0 ; i < POPULATION_SIZE; i+=2) {
        // Bitmasks with pc = 0.5
        bitset<POPULATION_BITS> bitmask1;
        bitset<POPULATION_BITS> child1;
        bitset<POPULATION_BITS> child2;
        for (int j = 0; j < POPULATION_BITS; j++) {
            bitmask1[j] = (rand() % 100) < 50 ? true : false;
        }
        child1 = bitmask1 & initial_population[i];
        bitset<POPULATION_BITS> bitmask2;
        for (int j = 0; j < POPULATION_BITS; j++) {
            bitmask2[j] = (rand() % 100) < 50 ? true : false;
        }
        child2 = bitmask2 & initial_population[i + 1];
        new_population[i] = child1;
        new_population[i + 1] = child2;
        cout << bitmask1 << " & " << initial_population[i] << " = " << child1 << endl; 
        cout << bitmask1 << " & " << initial_population[i] << " = " << child1 << endl; 
    }
}

void accented_crossing(bitset<POPULATION_BITS> initial_population[], 
bitset<POPULATION_BITS> new_population[]) {
    for (int i = 0 ; i < POPULATION_SIZE; i+=2) {
        // Accents
        bitset<POPULATION_BITS> accents;
        for (int j = 0; j < POPULATION_BITS; j++) {
            accents[j] = (rand() % 100) < 50 ? true : false;
        };  
        bitset<POPULATION_BITS> child1;
        bitset<POPULATION_BITS> child2;
        bitset<POPULATION_BITS> aux_parent1 = initial_population[i];
        bitset<POPULATION_BITS> aux_parent2 = initial_population[i + 1];
        // Crossing 
        for (int j = 0; j < POPULATION_BITS; j++) {
            if (accents[j] == true) {
                if (aux_parent1 == initial_population[i]) {
                    aux_parent1 = initial_population[i + 1];
                    aux_parent2 = initial_population[i];
                } else {
                    aux_parent1 = initial_population[i];
                    aux_parent2 = initial_population[i + 1];
                }
            }
            child1[j] = aux_parent1[j];
            child2[j] = aux_parent2[j];
        }
        new_population[i] = child1;
        new_population[i + 1] = child2;
        cout << "Accents: " << accents  << endl;
        cout << "Parent 1: " << initial_population[i] << " Parent 2: " << initial_population[i + 1] << endl; 
        cout << "Child 1: " << child1 << " Child 2: " << child2 << endl; 
    }
}