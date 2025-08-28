#include "matrix_operation.h"
#include <immintrin.h>

Matrix MatrixOperation::NaiveMatMul(const Matrix &A, const Matrix &B) {
	size_t n = A.getRows();
	size_t k = A.getCols();
	size_t m = B.getCols();

	if (k != B.getRows()) {
		throw std::invalid_argument("Matrix dimensions don't match for multiplication");
	}
	
	
	Matrix C(n,m);
	
	for(int i = 0; i < n ; i++) {
		for (int j = 0 ; j< m ; j++) {
			for(int l = 0; l < k; l++) {
				C(i,j) += A(i,l) * B(l,j);
			}
		}
	}
	
	return C;
}

// Loop reordered matrix multiplication (ikj order for better cache locality)
Matrix MatrixOperation::ReorderedMatMul(const Matrix& A, const Matrix& B) {
	size_t n = A.getRows();
	size_t k = A.getCols();
	size_t m = B.getCols();

	if (k != B.getRows()) {
		throw std::invalid_argument("Matrix dimensions don't match for multiplication");
	}
	
	
	Matrix C(n,m);
	
	for(int i = 0; i < n ; i++) {
		for (int l = 0 ; l < k; l++) {
			for(int j = 0; j < m; j++) {
				C(i,j) += A(i,l) * B(l,j);
			}
		}
	}


	return C;
}

// Loop unrolled matrix multiplication
Matrix MatrixOperation::UnrolledMatMul(const Matrix& A, const Matrix& B) {
	size_t n = A.getRows();
    size_t k = A.getCols();
    size_t m = B.getCols();

    if (k != B.getRows()) {
        throw std::invalid_argument("Matrix dimensions don't match for multiplication");
    }

    Matrix C(n, m);

    const int UNROLL = 4;

	for(int i = 0; i < n ; i++) {
		for (int l = 0 ; l < k; l++) {
			for(int j = 0; j < m; j += UNROLL) {
				C(i,j + 0) += A(i,l) * B(l,j + 0);
				C(i,j + 1) += A(i,l) * B(l,j + 1);
				C(i,j + 2) += A(i,l) * B(l,j + 2);
				C(i,j + 3) += A(i,l) * B(l,j + 3);
			}
		}
	}

    return C;
}

// Tiled (blocked) matrix multiplication for cache efficiency
Matrix MatrixOperation::TiledMatMul(const Matrix& A, const Matrix& B) {
	size_t n = A.getRows();
    size_t k = A.getCols();
    size_t m = B.getCols();

    if (k != B.getRows()) {
        throw std::invalid_argument("Matrix dimensions don't match for multiplication");
    }

    Matrix C(n, m);
    const int T = 64;   // tile size
	for (int i = 0; i < n; i += T) {
		for(int l = 0; l < k; l += T) {
			for (int j = 0; j < m; j += T) {
				for(int ii = i; ii < i + T; ii++) {
					for(int kk = l; kk < l + T; kk++) {
						for(int jj = j; jj < j + T; jj++) {
							// C[ii * n + jj] += A[ii * n + kk] * B[kk * k + jj];
							C(ii, jj) += A(ii, kk) * B(kk, jj);
						}
					}
				}
			}
		}
	}

    return C;
}

// SIMD vectorized matrix multiplication (using AVX2)
Matrix MatrixOperation::VectorizedMatMul(const Matrix& A, const Matrix& B) {
	size_t n = A.getRows();
    size_t k = A.getCols();
    size_t m = B.getCols();

    if (k != B.getRows()) {
        throw std::invalid_argument("Matrix dimensions don't match for multiplication");
    }
    Matrix C(n, m);
	int size = n;
	for (int i = 0; i < size; i++) {
		for (int k = 0; k < size; k++) {
			__m256d vectorA = _mm256_broadcast_sd(&A(i, k));
			for (int j = 0; j < size; j += 4) {
				__m256d vectorC = _mm256_loadu_pd(&C(i, j));
				__m256d vectorB = _mm256_loadu_pd(&B(k, j));

				__m256d mul = _mm256_mul_pd(vectorA, vectorB);
				vectorC = _mm256_add_pd(vectorC, mul);
				_mm256_storeu_pd(&C(i, j), vectorC);
			}
		}
	}	
    return C;
}

// Optimized matrix transpose
Matrix MatrixOperation::Transpose(const Matrix& A) {
	size_t rows = A.getRows();
	size_t cols = A.getCols();
	Matrix result(cols, rows);
	int tile_size = 128;
	for (size_t i = 0; i < rows; i += tile_size) {
		for (size_t j = 0; j < cols; j += tile_size) {
			for (size_t ii = i; ii < i + tile_size; ii++) {
				for (size_t jj = j; jj < j + tile_size; jj++) {
					result(jj, ii) = A(ii, jj);
				}
			}
		}
	}
	return result;
}
