#include <stdio.h>
#include <stdlib.h>

void fill_matrix(int **s, int x_len, int y_len, int draw_start, int draw_end,
                 int value_to_fill) {
  for (int i = 0; i < y_len; i++) {
    for (int j = 0; j < x_len; j++) {
      if (i > draw_start && i < draw_end && j > draw_start && j < draw_end) {
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
  int **s = (int **)initialize_matrix(10, 10);
  fill_matrix(s, 10, 10, 1, 8, 9);
  print_matrix(s, 10, 10);
  return 0;
}
