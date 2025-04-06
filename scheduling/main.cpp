// `n` activities `(0, ..., n-1)`
// `m` resource types `(0, ..., m-1)`
// `a[k]` = per-period availability of resource type `k`
// `d[i]` = duration of activity `i`
// `r[i][k]` = resource requirement of activity `i` w.r.t. resource type `k`
// activity `i` has `nrpr[i]` predecessors
// `pr[i][j]` is the activity number of the `j`th predecessor of activity `i`
// `nrsu`, `su`: same as `nrpr` and `pr` but for successors
// `of[i]`: what is the (optimal) finish time of activity `i`?

#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable : 4996)

#define _CRTDBG_MAP_ALLOC

#include <iostream>

#ifdef _DEBUG
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ACT 32
#define RES 4
#define SUC 10

int n, m, a[RES], d[ACT], r[ACT][RES], nrsu[ACT], su[ACT][SUC];
int nrpr[ACT], pr[ACT][SUC], of[ACT];

int input(void) {
  int i1, i2, i3;
  char filename[64];
  FILE *fp;
  printf("\n\n	Filename: ");
  scanf("%s", filename);
  strcat(filename, ".rcp");
  printf("\n\n	Reading file %s\n", filename);
  fp = fopen(filename, "r");
  if (fp == NULL) return 0;
  fscanf(fp, "%d %d", &n, &m);
  if (n > ACT || m > RES) return 0;
  for (i1 = 0; i1 < m; i1++) fscanf(fp, "%d", a + i1);
  for (i1 = 0; i1 < n; i1++) nrpr[i1] = 0;
  for (i1 = 0; i1 < n; i1++) {
    fscanf(fp, "%d", d + i1);
    for (i2 = 0; i2 < m; i2++) {
      fscanf(fp, "%d", r[i1] + i2);
      if (r[i1][i2] > a[i2]) return 0;
    }
    fscanf(fp, "%d", nrsu + i1);
    for (i2 = 0; i2 < nrsu[i1]; i2++) {
      fscanf(fp, "%d", &i3);
      if (i3 <= i1 || i3 > n) return 0;
      su[i1][i2] = --i3;
      pr[i3][nrpr[i3]++] = i1;
    }
  }
  fclose(fp);
  return 1;
}

void procedure(void) {
  int ps[ACT], dm, nrs, s[SUC], req[RES], i1, i2, i3, i4, i5;
  for (i1 = 0; i1 < n; i1++) ps[i1] = 0;
  nrs = 1;
  s[0] = of[0] = 0;
  while (ps[n - 1] == 0) {
    dm = INT_MAX;
    for (i1 = 0; i1 < nrs; i1++)
      if (of[s[i1]] < dm) dm = of[s[i1]];
    for (i1 = 0; i1 < nrs; i1++)
      if (of[s[i1]] == dm) {
        ps[s[i1]] = 1;
        for (i3 = 0; i3 < nrsu[s[i1]]; i3++) {
          i4 = su[s[i1]][i3];
          for (i5 = 0; i5 < nrpr[i4]; i5++)
            if (ps[pr[i4][i5]] == 0) break;
          if (i5 == nrpr[i4]) {
            s[nrs++] = i4;
            of[i4] = dm + d[i4];
          }
        }
        s[i1--] = s[--nrs];
      }
    for (i1 = 0; i1 < m; i1++) req[i1] = 0;
    for (i1 = 0; i1 < nrs; i1++)
      for (i2 = 0; i2 < m; i2++) req[i2] += r[s[i1]][i2];
    for (i1 = 0; i1 < m; i1++)
      if (req[i1] > a[i1]) break;
    if (i1 < m) { /*printf ("Resource conflict at %d\n“, dm);*/
      return;
    }
  }
  return;
}

int main(void) {
  int i1;
  double elapsed_time;
  clock_t start_time;
  if (input()) {
    start_time = clock();
    for (i1 = 0; i1 < 1000000; i1++) procedure();
    elapsed_time = (double)(clock() - start_time) / CLK_TCK;
    for (i1 = 0; i1 < n; i1++) printf("Activity %d: %d\n", i1, of[i1]);
    printf("\nComputation time: %.2f seconds\n", elapsed_time);
  } else
    printf("\nWrong input data\n");
  return 0;
}
