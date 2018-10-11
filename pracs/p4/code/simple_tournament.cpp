#include "gfx.h"
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
const int MUTATION_PROBABILITY = 10;
const int CROSS_POS = 4;
// Window Size
const int windowH = 750;
const int windowW = 1420;
// Plot Size
const int plotPadding = 70;
const int plotH = windowH - plotPadding;
const int plotW = windowW - plotPadding;
const int plotCx = plotW/2;
const int plotCy = plotH/2;
// Axis Position
const int x = plotH - plotPadding;

struct myseps : numpunct<char> { 
   // use ' as separator
   char do_thousands_sep() const { return ','; } 

   // digits are grouped by 3
   string do_grouping() const { return "\3"; }
};

void drawPlotFrame() {
	gfx_color(9, 71, 122);
	gfx_point(plotCx, plotCy);
	// X-Axis
	gfx_line(plotPadding, x, plotW - plotPadding, x);
	// Y-Axis
	gfx_line(plotPadding*2, plotPadding, plotPadding*2, plotH);
	gfx_color(0, 200, 100);
}


void printHistogram(int max_values[], int min_values[], int n)
{
	gfx_open(windowW, windowH, "Historigrama");
	gfx_color(0, 200, 100);
	int barPadding = (plotW - plotPadding*3)/n;
 	int delta = barPadding + plotPadding*2;
	int maxElement = *max_element(max_values, max_values + n);
    int maxElement_min = *max_element(min_values, min_values + n);
    int average_values[POPULATION_SIZE];
    // Calculate the average values
    for (int i = 0; i < POPULATION_SIZE; i++) {
        average_values[i] = (min_values[i] + max_values[i]) / 2;
    }
    int maxElement_average = *max_element(average_values, average_values + n);
	char str[12] = {'\0'};
	vector <tuple<int, int> > points;
    vector <tuple<int, int> > points_m;
    vector <tuple<int, int> > points_av;
	// Max values graph calculation
	for(int i=0, barPos=delta; i < n; i++)
	{
		int yBar = plotPadding;
		if (maxElement != max_values[i]) {
			yBar = x - (((double)max_values[i] * (plotH - 2*plotPadding) / (double)maxElement));
		}
		points.push_back(tuple<int, int>(barPos, (int)yBar));
		barPos+=barPadding;
	}

    // Min values graph calculation
    for(int i=0, barPos=delta; i < n; i++)
	{
		int yBar = plotPadding;
		yBar = x - (((double)min_values[i] * (plotH - 2*plotPadding) / (double)maxElement));
		points_m.push_back(tuple<int, int>(barPos, (int)yBar));
		barPos+=barPadding;
	}

    // Average values graph calculation
    for(int i=0, barPos=delta; i < n; i++)
	{
		int yBar = plotPadding;
		yBar = x - (((double)average_values[i] * (plotH - 2*plotPadding) / (double)maxElement));
		points_av.push_back(tuple<int, int>(barPos, (int)yBar));
		barPos+=barPadding;
	}
    while(1) {
    	gfx_clear();
		drawPlotFrame();
 		char str[12] = {'\0'};
    	for(int i=1; i <= n; i++)
 		{
 			stringstream ss;
            stringstream ss_min;
            stringstream ss_average;
            // Max values text
			ss.imbue(locale(locale(), new myseps));
			ss << max_values[i-1];  // printing to string stream with formating
			sprintf(str, "%s", ss.str().c_str());
			// Y text for min values
			gfx_color(9, 71, 122);
			gfx_text(get<0>(points[i-1]),  get<1>(points[i-1]) - 10, str);
            // Min values Text
            ss_min.imbue(locale(locale(), new myseps));
			ss_min << min_values[i-1];  // printing to string stream with formating
			sprintf(str, "%s", ss_min.str().c_str());
            gfx_text(get<0>(points_m[i-1]),  get<1>(points_m[i-1]) - 10, str);

            // Average values Text
            ss_average.imbue(locale(locale(), new myseps));
			ss_average << average_values[i-1];  // printing to string stream with formating
			sprintf(str, "%s", ss_average.str().c_str());
            gfx_text(get<0>(points_av[i-1]),  get<1>(points_av[i-1]) - 10, str);

			gfx_circle(get<0>(points[i-1]), get<1>(points[i-1]), 3);
			gfx_color(0, 200, 100);
			// Bar
			gfx_line(get<0>(points[i-1]), x, get<0>(points[i-1]), get<1>(points[i-1]));
			// X text
 			sprintf(str, "%d", i);
 			gfx_text(get<0>(points[i-1]), plotH - plotPadding + 20 , str);
			// Lines
			if (i < n) {
                // Max values
				gfx_line(get<0>(points[i-1]), get<1>(points[i-1]), get<0>(points[i]), get<1>(points[i]));
                // Min values
                gfx_color(255, 0, 0);
                gfx_line(get<0>(points_m[i-1]), get<1>(points_m[i-1]), get<0>(points_m[i]), 
                get<1>(points_m[i]));
                // Average values
                gfx_color(255, 255, 255);
                gfx_line(get<0>(points_av[i-1]), get<1>(points_av[i-1]), get<0>(points_av[i]), 
                get<1>(points_av[i]));
			}
 		}
 		if(gfx_event_waiting()){
 			if(gfx_wait() == 'q'){
 				break;
 			}
 		}
		usleep(41666); //24 por segundo
    }
}

unsigned int get_value(bitset<POPULATION_BITS>& p) {
    return (unsigned int)(p.to_ulong());
}

unsigned int calculate_aptitude(unsigned int value) {
    return (unsigned int)pow(value, 2);
}

void sort_individuals(bitset<POPULATION_BITS> old_population[]) {
    bitset<POPULATION_BITS> new_population[POPULATION_SIZE];
    map<int, bool> m;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        while(true) {
            int position = rand() % (POPULATION_SIZE + 1);
            if (m.find(i) == m.end()) {
                m[i] = true;
                new_population[i] = old_population[i];   
                break;
            } else {
                continue;
            }             
        }
    }
    for (int i = 0; i < POPULATION_SIZE; i++) {
        new_population[i] = old_population[i];
    }
}

bitset<POPULATION_BITS> tournament_selection(bitset<POPULATION_BITS> population[], unsigned int total) {
    sort_individuals(population);

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
    for (int i = 0; i < POPULATION_BITS; i++) {
        unsigned int value = rand() % (POPULATION_BITS);
        if (mutated_individual[value] == false) {
            mutated_individual.set(value, true);
        }
    }
    return mutated_individual;
}

unsigned int find_max(bitset<POPULATION_BITS> population[]) {
    unsigned int max = 0;
    for(int i = 0; i < POPULATION_SIZE; i++) {
        unsigned int value = (unsigned int)population[i].to_ulong();
        if (value > max) {
            max = value;
        }
    }
    return max;
}

unsigned int find_min(bitset<POPULATION_BITS> population[]) {
    unsigned int min = (unsigned int)population[0].to_ulong();
    for(int i = 0; i < POPULATION_SIZE; i++) {
        unsigned int value = (unsigned int)population[i].to_ulong();
        if (value < min) {
            min = value;
        }
    }
    return min;
}

int main(int argc, char *argv[]) {
    int NUM_GENERATIONS = 5;
    if (argc == 2) {
        NUM_GENERATIONS = atoi(argv[1]);
    }
    srand(time(0));
    int max_values[NUM_GENERATIONS];
    int min_values[NUM_GENERATIONS]; 
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

    for (int j = 0; j < NUM_GENERATIONS; j++) {
        // Parent Selection
        max_values[j] = calculate_aptitude(find_max(initial_population));
        min_values[j] = calculate_aptitude(find_min(initial_population));
        for (int i = 0; i < POPULATION_SIZE; i++) {
            cout << initial_population[i] << endl;
            descendancy[i] = tournament_selection(initial_population, total);
        }
        cout << endl << endl; 

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
        }
    }
    printHistogram(max_values, min_values, NUM_GENERATIONS);
    return 0;
}
