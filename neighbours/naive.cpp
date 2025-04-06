#include "HW3.cpp"

// #include "ListItem.h"  // outcomment this when you have added a ListItem class to your project workspace
#include <math.h>

// delta: the required distance between two "close" points
// nbPoints: number of points
// x[i], y[i]: x and y coordinates of point i


void procedure(){
	int count = 0;
	int i, j;
	for (i=0; i!=nbPoints; i++){
		for (j=0; j!=i; j++){
			if (sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2)) <= delta){ 
				count++;
			}
		}
	}
	printf("Count = %d\n", count);
}
