#include "gfx.h"
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <bits/stdc++.h>

const int centerX = 100; 
const int centerY = 100; 

using namespace std;
void drawFrame() {
	 	gfx_line(centerX, centerY, 0, 0);
}

void printHistogram(int arr[], int n)
{

	gfx_open(800, 600, "Historigrama");
	gfx_color(0, 200, 100);
 
 	int height = 500;
 	int width = 20;
 	int delta = 200;
    while(1) {
    	gfx_clear();
 		//drawFrame();
 		char str[12] = {'\0'};
    	for(int i=0, j=0; i < n; i++)
 		{
			sprintf(str, "%d", arr[i]);
 			gfx_line(delta + j, height, delta + j, delta - arr[i]*10);
 			gfx_text( delta + j, delta - arr[i]*10 - 10 , str);
 			sprintf(str, "%d", i + 1);
 			gfx_text( delta + j, height + 20 , str);
 			j+=20;
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
	srand(time(0));
	int arr[10] = { 10, 9, 12, 4, 5, 2,
                    8, 5, 3, 1 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printHistogram(arr, n);
    return 0;
}
