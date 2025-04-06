#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maxn 20000

typedef int mat[maxn + 1];

int n, b;
mat c, a, x;

void input(void) {
  int i;
  char filename[20];
  FILE *fp;
  printf("\n\n Give the problem name: ");
  scanf("%s", filename);
  strcat(filename, ".knp");
  fp = fopen(filename, "r");
  fscanf(fp, "%d %d", &n, &b);
  if (n > maxn) {
    printf("Too many objects\n\n");
    return;
  }
  for (i = 0; ++i <= n;) fscanf(fp, "%d %d", a + i, c + i);
  fclose(fp);
  return;
}

void output(void) {
  int i, j, k;
  printf("\n Objects: ");
  i = j = k = 0;
  while (++i <= n)
    if (x[i]) {
      printf(", %d", i);
      j += a[i];
      k += c[i];
    }
  printf("\n");
  printf("\n Weight = %d <= %d\n", j, b);
  printf("\n Value = %d\n", k);
  return;
}

void procedure(void);

int main() {
  double elapsed_time;
  clock_t start_time;
  input();
  start_time = clock();
  procedure();
  elapsed_time = (float)(clock() - start_time) / CLK_TCK;
  output();
  printf("\n Computation time: %.2f seconds\n", elapsed_time);
  getch();
  return 0;
}
