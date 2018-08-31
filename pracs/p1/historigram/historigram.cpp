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
    while(1) {
    	gfx_clear();
		drawPlotFrame();
 		char str[12] = {'\0'};
    	for(int i=0, barPos=delta; i < n; i++)
 		{
			sprintf(str, "%d", arr[i]);
			if (maxElement == arr[i]) {
 				gfx_line(barPos, x, barPos, plotPadding);
				gfx_color(9, 71, 122);
 				gfx_text(barPos, plotPadding - 10, str);
				gfx_color(0, 200, 100);
			} else {
				unsigned long long yBar = x - 
				(((double)arr[i] * (plotH - 2*plotPadding) / (double)maxElement));
				gfx_line(barPos, x, barPos, yBar);
				gfx_color(9, 71, 122);
				gfx_text(barPos, yBar - 10, str);
				gfx_color(0, 200, 100);
			}
 			sprintf(str, "%d", i + 1);
 			gfx_text(barPos, plotH-plotPadding + 20 , str);
 			barPos+=barPadding;
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
