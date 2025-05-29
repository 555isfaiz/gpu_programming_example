#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define DRAW_START 128
#define DRAW_END 512

void fill_matrix(int **s, 
                 int x_len, 
                 int y_len, 
                 int value_to_fill) {
  for (int i = 0; i < y_len; i++) {
    for (int j = 0; j < x_len; j++) {
      if (i > DRAW_START 
                && i < DRAW_END 
                && j > DRAW_START 
                && j < DRAW_END) {
        s[i][j] = value_to_fill;
      }
    }
  }
}

void fill_matrix_omp(int **s, 
                     int x_len, 
                     int y_len, 
                     int value_to_fill) {
  #pragma omp parallel for collapse(2)
  for (int i = 0; i < y_len; i++) {
    for (int j = 0; j < x_len; j++) {
      if (i > DRAW_START 
                && i < DRAW_END 
                && j > DRAW_START 
                && j < DRAW_END) {
        s[i][j] = value_to_fill;
      }
    }
  }
}

void print_matrix(int **s, int x_len, int y_len) {
  for (int i = 0; i < y_len; i++) {
    for (int j = 0; j < x_len; j++) {
      printf("%d, ", s[i][j]);
    }
    printf("\n");
  }
}

int64_t initialize_matrix(int rows, int cols) {
  int **matrix = (int **)malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++) {
    matrix[i] = (int *)malloc(cols * sizeof(int));
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = 0;
    }
  }
  return (int64_t)matrix;
}

int main() {
  int **s = (int **)initialize_matrix(32768, 32768);
  // printf("before: \n");
  // print_matrix(s, 32768, 32768);

  fill_matrix_omp(s, 32768, 32768, 9);

  // printf("after: \n");
  // print_matrix(s, 32768, 32768);
  return 0;
}


