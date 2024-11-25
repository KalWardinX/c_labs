import numpy as np

def matrix_multiplication(size):
    A = np.random.rand(size, size)
    B = np.random.rand(size, size)
    C = np.dot(A, B)  # Multiply A and B
    print(f"Matrix multiplication complete for {size}x{size} matrices.")

if __name__ == "__main__":
    matrix_multiplication(1000)
