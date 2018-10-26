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
const float MAX_R = 1.1;
const float MIN_R = 2 - MAX_R;
map<int, float> expected_values;

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


void printHistogram(float max_values[], float min_values[], int n)
{
	gfx_open(windowW, windowH, "Historigrama");
	gfx_color(0, 200, 100);
	int barPadding = (plotW - plotPadding*3)/n;
 	int delta = barPadding + plotPadding*2;
	float maxElement = *max_element(max_values, max_values + n);
    float maxElement_min = *max_element(min_values, min_values + n);
    double average_values[POPULATION_SIZE];
    // Calculate the average values
    for (int i = 0; i < POPULATION_SIZE; i++) {
        average_values[i] = ((double)min_values[i] + (double)max_values[i]) / 2.0;
    }
    float maxElement_average = *max_element(average_values, average_values + n);
	char str[12] = {'\0'};
	vector <tuple<float, float> > points;
    vector <tuple<float, float> > points_m;
    vector <tuple<float, float> > points_av;
	// Max values graph calculation
	for(int i=0, barPos=delta; i < n; i++)
	{
		float yBar = plotPadding;
		if (maxElement != max_values[i]) {
			yBar = x - (((double)max_values[i] * (plotH - 2*plotPadding) / (double)maxElement));
		}
		points.push_back(tuple<float, float>(barPos, yBar));
		barPos+=barPadding;
	}

    // Min values graph calculation
    for(int i=0, barPos=delta; i < n; i++)
	{
		float yBar = plotPadding;
		yBar = x - (((double)min_values[i] * (plotH - 2*plotPadding) / (double)maxElement));
		points_m.push_back(tuple<float, float>(barPos, yBar));
		barPos+=barPadding;
	}

    // Average values graph calculation
    for(int i=0, barPos=delta; i < n; i++)
	{
		int yBar = plotPadding;
		yBar = x - (((double)average_values[i] * (plotH - 2*plotPadding) / (double)maxElement));
		points_av.push_back(tuple<float, float>(barPos, yBar));
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

            // // Average values Text
            // ss_average.imbue(locale(locale(), new myseps));
			// ss_average << average_values[i-1];  // printing to string stream with formating
			// sprintf(str, "%s", ss_average.str().c_str());
            // gfx_text(get<0>(points_av[i-1]),  get<1>(points_av[i-1]) - 10, str);

			gfx_circle(get<0>(points[i-1]), get<1>(points[i-1]), 3);
			gfx_color(0, 200, 100);
			// Bar
			// gfx_line(get<0>(points[i-1]), x, get<0>(points[i-1]), get<1>(points[i-1]));
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
                gfx_line((int)get<0>(points_av[i-1]), (int)get<1>(points_av[i-1]), (int)get<0>(points_av[i]), 
                (int)get<1>(points_av[i]));
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

int get_value(bitset<POPULATION_BITS>& p) {
    return (int)(p.to_ulong());
}

float get_expected_value(bitset<POPULATION_BITS>& p) {
    return expected_values[(int)(p.to_ulong())];
}


float calculate_aptitude(int value) {
    return (int)abs((value - 5) / 2 + sin(value));
}

void sort_individuals(bitset<POPULATION_BITS> old_population[]) {
    bitset<POPULATION_BITS> new_population[POPULATION_SIZE];
    map<int, bool> m;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        while(true) {
            int position = rand() % (POPULATION_SIZE + 1);
            if (m.find(position) == m.end()) {
                m[position] = true;
                new_population[i] = old_population[position];   
                break;
            }         
        }
    }
    for (int i = 0; i < POPULATION_SIZE; i++) {
        old_population[i] = new_population[i];
    }
}

bitset<POPULATION_BITS> tournament_selection(bitset<POPULATION_BITS> p1, bitset<POPULATION_BITS> p2) {
    float flip = (rand()) / static_cast <float> (RAND_MAX);
    float aptitude_1 = calculate_aptitude(get_expected_value(p1));
    float aptitude_2 = calculate_aptitude(get_expected_value(p2));
    if (aptitude_1 < aptitude_2 && flip >= 0.70) {
        return p2;
    } else if (aptitude_1 < aptitude_2 && flip < 0.70) {
        return p1;
    } else if (aptitude_1 > aptitude_2 && flip >= 0.70) {
        return p1;
    } else {
        return p1;
    }
}

bitset<POPULATION_BITS> cross(bitset<POPULATION_BITS> &p1, bitset<POPULATION_BITS> &p2, 
    int cross_point) {
    bitset<POPULATION_BITS> child = p1;
    child.set(cross_point, p2[cross_point]);
    return child;
}

bool has_mutation(int mutations[], int num_individual, int num_mutations){
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
        int value = rand() % (POPULATION_BITS);
        if (mutated_individual[value] == false) {
            mutated_individual.set(value, true);
        }
    }
    return mutated_individual;
}

int find_max(bitset<POPULATION_BITS> population[]) {
    int max = 0;
    for(int i = 0; i < POPULATION_SIZE; i++) {
        int value = (int)population[i].to_ulong();
        if (value > max) {
            max = value;
        }
    }
    return max;
}

int find_min(bitset<POPULATION_BITS> population[]) {
    int min = (int)population[0].to_ulong();
    for(int i = 0; i < POPULATION_SIZE; i++) {
        int value = (int)population[i].to_ulong();
        if (value < min) {
            min = value;
        }
    }
    return min;
}

void simple_ranking(bitset<POPULATION_BITS> population[]) {
    int values[POPULATION_SIZE];
    int n = sizeof(values) / sizeof(values[0]); 
    for(int i = 0; i < POPULATION_SIZE; i++) {
        values[i] = get_value(population[i]);
    }
    // Ascendant sort
    sort(values, values+n);
    // Rank the values
    for (int i = 1; i <= POPULATION_SIZE; i++) {
        expected_values[values[i]] = MIN_R + (MAX_R - MIN_R) * (i - 1) / (POPULATION_SIZE - 1);
    }
}


bitset<POPULATION_BITS> roulette_selection(bitset<POPULATION_BITS> population[], float total) {
    float r = rand() % ((int)total + 1);
    float sum = 0;
    int i;
    for(i=0; i < POPULATION_SIZE && sum < r; i++) {
        // Evaluation
        float value = get_expected_value(population[i]);
        float aptitude = calculate_aptitude(value);
        sum += aptitude;
    }
    return population[i];
}

int main(int argc, char *argv[]) {
    int NUM_GENERATIONS = 5;
    if (argc == 2) {
        NUM_GENERATIONS = atoi(argv[1]);
    }
    srand(time(0));
    float max_values[NUM_GENERATIONS];
    float min_values[NUM_GENERATIONS]; 
	bitset<POPULATION_BITS> initial_population[POPULATION_SIZE];
    bitset<POPULATION_BITS> descendancy[POPULATION_SIZE];
    float total = 0;

    // Initialization, evaluation
    for (int i = 0; i < POPULATION_SIZE; i++) {
        int random_value = rand() % (MAX_INDIVIDUAL_SIZE - MIN_INDIVIDUAL_SIZE + 1) 
        + MIN_INDIVIDUAL_SIZE;
        // Init
        initial_population[i] = bitset<POPULATION_BITS>(random_value);
    }


    for (int j = 0; j < NUM_GENERATIONS; j++) {
        // Rank the population
        simple_ranking(initial_population);
        for (int i = 0; i < POPULATION_SIZE; i++) {
            total += get_expected_value(initial_population[i]);
        }
        max_values[j] = calculate_aptitude(find_max(initial_population));
        min_values[j] = calculate_aptitude(find_min(initial_population));
        // Parent Selection
        for (int i = 0; i < POPULATION_SIZE; i++) {
            descendancy[i] = roulette_selection(initial_population, total);
        }

        // Next Generation
        cout << endl;
        for (int i = 0; i < POPULATION_SIZE; i++) {
            initial_population[i] = descendancy[i];
        }

        // Cross and Mutation
        // Mutar aleatoriamente el individuo
        int num_indiv_mutar = POPULATION_SIZE / MUTATION_PROBABILITY;
        int mutations[num_indiv_mutar];
        total = 0;
        for (int i = 0; i < num_indiv_mutar; i++) {
            mutations[i] = rand() % (POPULATION_SIZE + 1);
        }
        for (int i = 0; i < POPULATION_SIZE; i+=2) {
            // Cross
            descendancy[i] = cross(initial_population[i], initial_population[i + 1], CROSS_POS);
            descendancy[i + 1] = cross(initial_population[i + 1], initial_population[i], CROSS_POS);
            // Mutation
            if (has_mutation(mutations, i, num_indiv_mutar)) {
                descendancy[i] = mutate(descendancy[i]);
            }
            if (has_mutation(mutations, i + 1, num_indiv_mutar)) {
                descendancy[i + 1] = mutate(descendancy[i + 1]);
            }
            // Evaluation
            int value1 = get_expected_value(descendancy[i]);
            int value2 = get_expected_value(descendancy[i + 1]);
            float aptitude1 = calculate_aptitude(value1);
            float aptitude2 = calculate_aptitude(value2);
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
