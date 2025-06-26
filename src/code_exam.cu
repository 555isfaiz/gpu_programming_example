#include <stdio.h>
#include <cuda_runtime.h>

#define DRAW_START 128
#define DRAW_END 1024

// CUDA kernel to fill matrix (row-major order)
__global__ void fill_matrix_kernel(int* matrix, int rows, int cols, int value) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row > DRAW_START && row < DRAW_END && col < DRAW_END && col > DRAW_START) {
        int idx = row * cols + col;
        matrix[idx] = value;
    }
}

void print_matrix(int *s, int x_len, int y_len) {
  for (int i = 0; i < y_len; i++) {
    for (int j = 0; j < x_len; j++) {
      printf("%d, ", s[i * x_len + j]);
    }
    printf("\n");
  }
}

void initialize_matrix(int *matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i * rows + j] = 0;
    }
  }
}

int main() {
    const int rows = 32768;
    const int cols = 32768;
    const size_t size = rows * cols * sizeof(int);
    
    // Host memory
    int* h_matrix = (int *)malloc(size);
    // initialize_matrix(h_matrix, rows, cols);
    
    // Device memory
    int* d_matrix;
    cudaMalloc((void **)&d_matrix, size);

    // cudaMemcpy(d_matrix, h_matrix, size, cudaMemcpyHostToDevice);
    
    // Define grid and block dimensions
    dim3 block(32, 32);  // 256 threads per block
    dim3 grid(
        (cols + block.x - 1) / block.x,  // ceil(cols/block.x)
        (rows + block.y - 1) / block.y   // ceil(rows/block.y)
    );
    
    // Launch kernel
    fill_matrix_kernel<<<grid, block>>>(d_matrix, rows, cols, 9);
    // cudaDeviceSynchronize();
    
    // Copy result back to host
    // cudaMemcpy(h_matrix, d_matrix, size, cudaMemcpyDeviceToHost);
    
    // Verify values
    // print_matrix(h_matrix, rows, cols);
    
    // Cleanup
    free(h_matrix);
    cudaFree(d_matrix);
    
    return 0;
}
