#include <stdio.h>
#include <time.h>
#include <immintrin.h>

#define M 400
#define N 600
#define K 800

//使用SIMD指令执行矩阵乘法，一条SIMD指令完成8个float类型数据的运算
void matrixMul_SIMD(float a[][K], float b[][N], float c[][N]) {
	__m256 va, vb, sum, prod ;//__m256存储256位，将其分为8部分，每部分为一个float类型的数
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j += 8) {
			sum = _mm256_loadu_ps(&c[i][j]);//读入从c[i][j]开始的8个float类型数
			for (int k = 0; k < K; k ++) {
				va = _mm256_set1_ps(a[i][k]);//读入a[i][k]并复制7个扩展成8个float类型数
				vb = _mm256_loadu_ps(&b[k][j]);//读入从b[k][j]开始的8个float类型数
				prod = _mm256_mul_ps(va, vb);//将va和vb中对应位置的float类型数相乘
				sum = _mm256_add_ps(sum, prod);//将sum和prod中对应位置的float类型数相加
			}
			_mm256_storeu_ps(&c[i][j], sum);//将sum中的8个float类型数存到从c[i][j]开始的内存空间中
		}
	}
}

//未优化的矩阵乘法
void matrixMul_base(float a[][K], float b[][N], float c[][N]) {
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < K; ++k)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
}

int main() {
	float a[M][K], b[K][N], c[M][N]; 
	int i, j, k;
	clock_t  start, stop;
	//初始化矩阵a和c
	for (i = 0; i < M; i++) {
		for (k = 0; k < K; k++)
		{
			a[i][k] = i * 0.02 + k * 0.01;
		}
		for (j = 0; j < N; j++)
		{
			c[i][j] = 0.0;
		}
	}
	//初始化矩阵b
	for (k = 0; k < K; k++) {
		for (j = 0; j < N; j++)
		{
			b[k][j] = k * 0.01 + j * 0.02;
		}
	}
	start = clock();
	matrixMul_base(a, b, c);
	stop = clock();
	printf("The time of bsae matrix multiplication(float):%f\n", (double)(stop - start) / CLOCKS_PER_SEC);
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
			c[i][j] = 0.0;
	start = clock();
	matrixMul_SIMD(a, b, c);
	stop = clock();
	printf("The time of matrix multiplication with SIMD(float):%f\n", (double)(stop - start) / CLOCKS_PER_SEC);
	return 0;
}
