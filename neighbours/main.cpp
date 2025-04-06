#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// hide unsafe warnings wrt deprecated input/output commands
#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable : 4996)

// memory leak detection
#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>

#include <iostream>

#ifdef _DEBUG
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

double *x, *y;
int nbPoints, maxCoord;
int delta;

void initPoints() {
  x = new double[nbPoints];
  y = new double[nbPoints];
  srand(2015);
  double eps = 0.000001f;

  int acc = 10000;

  for (int i = 0; i != nbPoints; i++) {
    x[i] = (((double)rand()) / RAND_MAX) * maxCoord;
    if (x[i] == maxCoord) x[i] -= eps;
    y[i] = (((double)rand()) / RAND_MAX) * maxCoord;
    if (y[i] == maxCoord) y[i] -= eps;
  }
}

void procedure();

int main() {
  double elapsed_time;
  clock_t start_time;
  nbPoints = 1000;
  maxCoord = 10;
  delta = 2;  // find the number of point pairs within distance <delta> of one
              // another
  printf("Generating %d points...", nbPoints);
  initPoints();
  printf("done!\n\n");
  //	printf("Press any key to start...\n"); getchar();
  start_time = clock();

  procedure();

  elapsed_time = (double)(clock() - start_time) / CLK_TCK;
  delete x;
  delete y;
  printf("Computation time: %.2f seconds\n", elapsed_time);
  printf("Press any key to continue...\n");
  getchar();
  _CrtDumpMemoryLeaks();
  return 0;
}

// TODO: Create a Single Document Interface (SDI) GUI application that
// visualizes the checks performed by the "advanced" algorithm of HW3

// - The animation should start when the user clicks on the menu Animation ->
// Start
// - The animation is executed by a separate thread
