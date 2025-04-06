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

#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maxcities 2000

typedef int list[maxcities + 1];
typedef int matrix[maxcities + 1][maxcities + 1];

int n;
double comp_time;
char choice[20];
list x, y, cities;
matrix dist;

void input(void) {
  int i, j, t;
  char filename[20];
  FILE *fp;
  printf("\n\n	Give the solution type: ");
  scanf("%s", choice);
  printf("\n\n	Give the problem name: ");
  scanf("%s", filename);
  strcat(filename, ".tsp");
  printf("\n\n	Give the allowed computation time: ");
  scanf("%d", &t);
  comp_time = (double)t;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("No such file\n\n");
    return;
  }
  fscanf(fp, "%d", &n);
  if (n > maxcities) {
    printf("Too many cities\n\n");
    return;
  }
  for (i = 0; ++i <= n;) {
    fscanf(fp, "%d %d", x + i, y + i);
    dist[i][i] = 0;
  }
  for (i = 0; ++i < n;)
    for (j = i; ++j <= n;)
      dist[i][j] = dist[j][i] =
          (int)sqrt((double)(x[i] - x[j]) * (x[i] - x[j]) +
                    (y[i] - y[j]) * (y[i] - y[j]));
  // for (i = 0; ++i <= n;) {for (j = 0; ++j <= n;) printf ("%5d", dist[i][j]);
  // printf ("\n");}
  fclose(fp);
  return;
}

void output(void) {
  int i, distance;
  list check;
  for (i = 0; ++i <= n;) check[i] = 0;
  distance = 0;
  cities[0] = cities[n];
  for (i = 0; ++i <= n;) { /*printf ("%5d", cities[i]);*/
    distance += dist[cities[i - 1]][cities[i]];
    check[cities[i]]++;
  }
  printf("\n\nDistance = %d\n", distance);
  for (i = 0; ++i <= n;)
    if (check[i] != 1) printf("Wrong solution!!!\n");
  return;
}

void TS(void);
void SA(void);
void GA(void);

clock_t start_time;

int main() {
  double elapsed_time;
  input();
  int x = 0;
  if (choice[0] == 65) x = 2;
  for (int i = 0; i <= x; i++) {
    start_time = clock();
    if (choice[0] == 84) TS();
    if (choice[0] == 83) SA();
    if (choice[0] == 71) GA();
    if (choice[0] == 65) {
      if (i == 0) TS();
      if (i == 1) SA();
      if (i == 2) GA();
    }
    elapsed_time = (float)(clock() - start_time) / CLK_TCK;
    output();
    printf("\n	Computation time: %.2f seconds\n", elapsed_time);
  }
  _CrtDumpMemoryLeaks();
  getch();
  return 0;
}

// Make sure that your code stops in time : int count = 0;
// double elapsed;
// if (++count > 1000) {
//   elapsed = clock() – start_time;
//   if (elapsed > comp_time * 1000) return;
//   count = 0;
// }

// There was room for more creativity in solving the TSP
// through metaheuristics:

// - Choose one direction only for the tour
// - E.g., start with tour from left-most node over top-most node over
// right-most node to bottom-most node and then perform insertion algorithm
// (possibly with different orders of remaining cities)
// - Why not consider pigeonholing in order to determine which cities are close
// to one another?
// - One could also start with the convex hull of all points
// - In GA, one could work with only the links that are present in both parents
// - etc.
