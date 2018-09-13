#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <locale>
#include <string>
#include <sstream>
#include<iomanip>
#include <bits/stdc++.h>

using namespace std;

const int num_alelo = 10;


void binary_representation() {
	int individual[num_alelo];
	cout << "\n[";
	for (int i = 0; i < num_alelo; i++) {
		individual[i] = (rand() % 2);
		if (i + 1 == num_alelo) {
			cout << individual[i] << "]\n\n";
		} else {
			cout << individual[i] << ", ";
		}
	}
}

int xor_c(int a, int b) { return (a == b) ? 0 : 1; } 

void gray_representation() 
{ 
	int binary[num_alelo];
	int gray[num_alelo];
	cout << "\n[";
	for (int i = 0; i < num_alelo; i++) {
		int value = (rand() % 2); 
		binary[i] = value;
		if (i + 1 == num_alelo) {
			cout << value << "] => ";
		} else {
			cout << value << ", ";
		}
	}
    gray[0] = binary[0]; 
	cout << "[";
    for (int i = 1; i < num_alelo; i++) {
		int value = xor_c(binary[i - 1], binary[i]); 
        gray[i] = value; 
    } 

	for (int i = 0; i < num_alelo; i++) {
		if (i + 1 == num_alelo) {
			cout << gray[i] << "]\n";
		} else {
			cout << gray[i] << ", ";
		}
    } 
} 

float random_float(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void real_representation() {
	float individual[num_alelo];
	cout << "\n[";
	for (int i = 0; i < num_alelo; i++) {
		float value = random_float(1, 10);
		individual[i] = value;
		if (i + 1 == num_alelo) {
			cout << value << "]\n";
		} else {
			cout << value << ", ";
		}
	}
}

void integer_representation() {
	int individual[num_alelo];
	cout << "\n[";
	for (int i = 0; i < num_alelo; i++) {
		int value = random() % 10;
		individual[i] = value;
		if (i + 1 == num_alelo) {
			cout << value << "]\n";
		} else {
			cout << value << ", ";
		}
	}
}

int main(int argc, char *argv[])
{
	srand(time(0));
	int option = 0;
	while(option != 5) {
		cout << "Ingrese la opción: " << endl << "	1: Representación Binaria" <<
		endl << "	2: Representación Gray" << endl << "	3: Representación real" <<
		endl << "	4: Representación entera" << endl << "	5: Salir" << endl;
		scanf("%d", &option);
		switch(option) {
			case 1:
				cout << "Representación Binaria" << endl;
				binary_representation();
			break;
			case 2:
				cout << "Representación Gray" << endl;
				gray_representation();
			break;
			case 3:
				cout << "Representación Real" << endl;
				real_representation();
			break;
			case 4:
				cout << "Representación Entera" << endl;
				integer_representation();
			break;
			default:
				break;
		}
		fflush(stdin);
	}
    return 0;
}
