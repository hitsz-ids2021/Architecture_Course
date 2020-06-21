#include <stdio.h>
#include <time.h>
#include <immintrin.h>

#define M 700
#define N 600
#define K 800

//两个向量逐位相乘后相加
void hardware_dot(float *accumulator, const float *a_slice, const float *b_slice) {
	float total = 0.0;
	for (int k = 0; k < 8; ++k) {
		total += a_slice[k] * b_slice[k];
	}
	*accumulator += total;
}

//标量与向量相乘
void hardware_saxpy(float *accumulator, float a, const float *input) {
	for (int k = 0; k < 8; ++k) {
		accumulator[k] += a * input[k];
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

//转置矩阵B后的矩阵乘法
void matrixMul_transpose(float a[][K], float b[][K], float c[][N]) {
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < K; ++k)
				c[i][j] += a[i][k] * b[j][k];
		}
	}
}

//转置矩阵B后8个元素一起相乘的矩阵乘法
void matrixMul_transpose_8_element_product(float a[][K], float b[][K], float c[][N]) {
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < K; k+=8)
				hardware_dot(&c[i][j], &a[i][k], &b[j][k]);
		}
	}
}

//未转置矩阵B的8个元素一起相乘的矩阵乘法
void matrixMul_8_element_product(float a[][K], float b[][N], float c[][N]) {
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; j+=8) {
			for (int k = 0; k < K; ++k)
				hardware_saxpy(&c[i][j], a[i][k], &b[k][j]);
		}
	}
}

//转置矩阵B后使用SIMD指令执行矩阵乘法
void matrixMul_transpose_SIMD(float a[][K], float b[][K], float c[][N]) {
	__m256 va, vb, sum, prod, prod_sum;//__m256存储256位，将其分为8部分，每部分为一个float类型的数
	__m128 total, sum_high, sum_low, result;//__m128存储128位，将其分为4部分，每部分为一个float类型的数
	float d[4];//SIMD指令每次至少会向内存写入128位，因此无法直接对矩阵c的单个元素写入，使用数组d来暂存结果
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			total = _mm_broadcast_ss(&c[i][j]);//读入c[i][j]并复制3个扩展成4个float类型数
			for (int k = 0; k < K; k += 8) {
				va = _mm256_loadu_ps(&a[i][k]);//读入从a[i][k]开始的8个float类型数
				vb = _mm256_loadu_ps(&b[j][k]);//读入从b[j][k]开始的8个float类型数
				prod = _mm256_mul_ps(va, vb);//将va和vb中对应位置的float类型数相乘
				//v3 = _mm256_hadd_ps(v1, v2)实现:
				//v3[0]=v1[0]+v1[1],v3[1]=v1[2]+v1[3],v3[2]=v2[0]+v2[1],v3[3]=v2[2]+v2[3],
				//v3[4]=v1[4]+v1[4],v3[5]=v1[6]+v1[7],v3[6]=v2[4]+v2[5],v3[7]=v2[6]+v2[7]
				prod_sum = _mm256_hadd_ps(prod, prod);//prod_sum[0]=prod[0]+prod[1]，
								      //prod_sum[1]=prod[2]+prod[3]，
								      //prod_sum[4]=prod[4]+prod[5]，
								      //prod_sum[5]=prod[6]+prod[7]，
				sum = _mm256_hadd_ps(prod_sum, prod_sum);//sum[0]=prod[0]+prod[1]+prod[2]+prod[3]
									 //sum[4]=prod[4]+prod[5]+prod[6]+prod[7]
				sum_low = _mm256_extractf128_ps(sum, 0);//取sum的低128位
				sum_high = _mm256_extractf128_ps(sum, 1);//取sum的高128位
				result = _mm_add_ps(sum_high, sum_low);//result[0]=sum[0]+sum[4]
				total = _mm_add_ps(total, result);//与c[i][j]累加
			}
			_mm_storeu_ps(&d[0], total);//将total中的4个float类型数存到从d[0]开始的内存空间中
			c[i][j] = d[0];//将结果写会c[i][j]
		}
	}
}

int main() {
	float a[M][K], b[K][N], c[M][N], transpose_b[N][K]; 
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
	//转制矩阵b
	for (k = 0; k < K; k++) {
		for (j = 0; j < N; j++)
		{
			transpose_b[j][k] = b[k][j];
		}
	}
	start = clock();
	matrixMul_base(a, b, c);
	stop = clock();
	printf("The time of bsae matrix multiplication:%f\n", (double)(stop - start) / CLOCKS_PER_SEC);
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
			c[i][j] = 0.0;
	start = clock();
	matrixMul_transpose(a, transpose_b, c);
	stop = clock();
	printf("The time of matrix multiplication with transpose:%f\n", (double)(stop - start) / CLOCKS_PER_SEC);
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
			c[i][j] = 0.0;
	start = clock();
	matrixMul_transpose_8_element_product(a, transpose_b, c);
	stop = clock();
	printf("The time of matrix multiplication with transpose and 8_element product:%f\n", (double)(stop - start) / CLOCKS_PER_SEC);
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
			c[i][j] = 0.0;
	start = clock();
	matrixMul_8_element_product(a, b, c);
	stop = clock();
	printf("The time of matrix multiplication with 8_element product:%f\n", (double)(stop - start) / CLOCKS_PER_SEC);
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
			c[i][j] = 0.0;
	start = clock();
	matrixMul_transpose_SIMD(a, transpose_b, c);
	stop = clock();
	printf("The time of matrix multiplication with transpose and SIMD:%f\n", (double)(stop - start) / CLOCKS_PER_SEC);
	return 0;
}
