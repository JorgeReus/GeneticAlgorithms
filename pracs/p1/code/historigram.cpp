#include "gfx.h"
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <bits/stdc++.h>

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

using namespace std;
void drawPlotFrame() {
	gfx_color(9, 71, 122);
	gfx_point(plotCx, plotCy);
	// X-Axis
	gfx_line(plotPadding, x, plotW - plotPadding, x);
	// Y-Axis
	gfx_line(plotPadding*2, plotPadding, plotPadding*2, plotH);
	gfx_color(0, 200, 100);
}

void printHistogram(int arr[], int n)
{
	gfx_open(windowW, windowH, "Historigrama");
	gfx_color(0, 200, 100);
	int barPadding = (plotW - plotPadding*3)/n;
 	int delta = barPadding + plotPadding*2;
	int maxElement = *max_element(arr, arr + n);
	char str[12] = {'\0'};
	vector <tuple<int, int> > points;
	// Calculate points
	for(int i=0, barPos=delta; i < n; i++)
	{
		int yBar = plotPadding;
		if (maxElement != arr[i]) {
			yBar = x - (((double)arr[i] * (plotH - 2*plotPadding) / (double)maxElement));
		}
		points.push_back(tuple<int, int>(barPos, (int)yBar));
		barPos+=barPadding;
	}
    while(1) {
    	gfx_clear();
		drawPlotFrame();
 		char str[12] = {'\0'};
    	for(int i=1; i <= n; i++)
 		{
			sprintf(str, "%d", arr[i-1]);
			// Y text
			gfx_color(9, 71, 122);
			gfx_text(get<0>(points[i-1]),  get<1>(points[i-1]) - 10, str);
			gfx_color(0, 200, 100);
			// Bar
			gfx_line(get<0>(points[i-1]), x, get<0>(points[i-1]), get<1>(points[i-1]));
			// X text
 			sprintf(str, "%d", i);
 			gfx_text(get<0>(points[i-1]), plotH - plotPadding + 20 , str);
			// Lines
			if (i < n) {
				gfx_line(get<0>(points[i-1]), get<1>(points[i-1]), get<0>(points[i]), get<1>(points[i]));
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


int main(int argc, char *argv[])
{
	int n = 10;
	if(argc == 2){
		n = atoi(argv[1]);
	}
	srand(time(0));
	int arr[n];
	for(int i=0; i < n; i++) {
		arr[i] = rand() % (100 + 1) + 1;
	}
    printHistogram(arr, n);
    return 0;
}
