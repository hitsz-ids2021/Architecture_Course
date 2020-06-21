#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1024

//未优化的矩阵乘法
void matrixMul_base(float **a, float **b, float **c, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
}

//矩阵加法
void matrixAdd(float **a, float **b, float **c, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

//矩阵减法
void matrixSub(float **a, float **b, float **c, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			c[i][j] = a[i][j] - b[i][j];
		}
	}
}

//Strassen算法
void matrixMul_Strassen(float **a, float **b, float **c, int size) {
	if (size < 16) 		//当矩阵大小小于16时，使用普通矩阵乘法（递归退出的条件）
		matrixMul_base(a, b, c, size);
	else {
		int n = size / 2;
		//初始化临时变量
		float **A11 = (float **)malloc(sizeof(float *) * n); 
		float **A12 = (float **)malloc(sizeof(float *) * n); 
		float **A21 = (float **)malloc(sizeof(float *) * n); 
		float **A22 = (float **)malloc(sizeof(float *) * n); 
		float **B11 = (float **)malloc(sizeof(float *) * n); 
		float **B12 = (float **)malloc(sizeof(float *) * n); 
		float **B21 = (float **)malloc(sizeof(float *) * n); 
		float **B22 = (float **)malloc(sizeof(float *) * n);
		float **C11 = (float **)malloc(sizeof(float *) * n); 
		float **C12 = (float **)malloc(sizeof(float *) * n); 
		float **C21 = (float **)malloc(sizeof(float *) * n); 
		float **C22 = (float **)malloc(sizeof(float *) * n);
		float **P1 = (float **)malloc(sizeof(float *) * n);
		float **P2 = (float **)malloc(sizeof(float *) * n);
		float **P3 = (float **)malloc(sizeof(float *) * n);
		float **P4 = (float **)malloc(sizeof(float *) * n);
		float **P5 = (float **)malloc(sizeof(float *) * n);
		float **P6 = (float **)malloc(sizeof(float *) * n);
		float **P7 = (float **)malloc(sizeof(float *) * n);
		float **AResult = (float **)malloc(sizeof(float *) * n); 
		float **BResult = (float **)malloc(sizeof(float *) * n); 
		for (int i = 0; i < n; i++) {
			A11[i] = (float *)malloc(sizeof(float) * n);
			A12[i] = (float *)malloc(sizeof(float) * n);
			A21[i] = (float *)malloc(sizeof(float) * n);
			A22[i] = (float *)malloc(sizeof(float) * n);
			B11[i] = (float *)malloc(sizeof(float) * n);
			B12[i] = (float *)malloc(sizeof(float) * n);
			B21[i] = (float *)malloc(sizeof(float) * n);
			B22[i] = (float *)malloc(sizeof(float) * n);
			C11[i] = (float *)malloc(sizeof(float) * n);
			C12[i] = (float *)malloc(sizeof(float) * n);
			C21[i] = (float *)malloc(sizeof(float) * n);
			C22[i] = (float *)malloc(sizeof(float) * n);
			P1[i] = (float *)malloc(sizeof(float) * n);
			P2[i] = (float *)malloc(sizeof(float) * n);
			P3[i] = (float *)malloc(sizeof(float) * n);
			P4[i] = (float *)malloc(sizeof(float) * n);
			P5[i] = (float *)malloc(sizeof(float) * n);
			P6[i] = (float *)malloc(sizeof(float) * n);
			P7[i] = (float *)malloc(sizeof(float) * n);
			AResult[i] = (float *)malloc(sizeof(float) * n);
			BResult[i] = (float *)malloc(sizeof(float) * n);
			//将矩阵拆分成大小相等的4部分
			for (int j = 0; j < n; j++)
			{
				A11[i][j] = a[i][j];
				A12[i][j] = a[i][j + n];
				A21[i][j] = a[i + n][j];
				A22[i][j] = a[i + n][j + n];
				B11[i][j] = b[i][j];
				B12[i][j] = b[i][j + n];
				B21[i][j] = b[i + n][j];
				B22[i][j] = b[i + n][j + n];

			}
		}
		//P1=(A11+A22)(B11+B22)
		matrixAdd(A11, A22, AResult, n);
		matrixAdd(B11, B22, BResult, n);
		matrixMul_Strassen(AResult, BResult, P1, n);
		//P2=(A21+A22)B11
		matrixAdd(A21, A22, AResult, n);
		matrixMul_Strassen(AResult, B11, P2, n);
		//P3=A11(B12-B22)
		matrixSub(B12, B22, BResult, n);
		matrixMul_Strassen(A11, BResult, P3, n);
		//P4=A22(B21-B11)
		matrixSub(B21, B11, BResult, n);
		matrixMul_Strassen(A22, BResult, P4, n);
		//P5=(A11+A12)B22
		matrixAdd(A11, A12, AResult, n);
		matrixMul_Strassen(AResult, B22, P5, n);
		//P6=(A21-A11)(B11+B12)
		matrixSub(A21, A11, AResult, n);
		matrixAdd(B11, B12, BResult, n);
		matrixMul_Strassen(AResult, BResult, P6, n);
		//P7=(A12-A22)(B21+B22)
		matrixSub(A12, A22, AResult, n);
		matrixAdd(B21, B22, BResult, n);
		matrixMul_Strassen(AResult, BResult, P7, n);
		//C11=P1+P4-P5+P7;
		matrixAdd(P1, P4, AResult, n);
		matrixSub(AResult, P5, BResult, n);
		matrixAdd(BResult, P7, C11, n);
		//C12=P3+P5;
		matrixAdd(P3, P5, C12, n);
		//C21=P2+P4;
		matrixAdd(P2, P4, C21, n);
		//C22=P1-P2+P3+P6;
		matrixSub(P1, P2, AResult, n);
		matrixAdd(AResult, P3, BResult, n);
		matrixAdd(BResult, P6, C22, n);
		//将结果写会矩阵c
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				c[i][j] = C11[i][j];
				c[i][j + n] = C12[i][j];
				c[i + n][j] = C21[i][j];
				c[i + n][j + n] = C22[i][j];
			}
		}
		//释放临时变量
		for (int i = 0; i < n; i++) {
			free(A11[i]);
			free(A12[i]);
			free(A21[i]);
			free(A22[i]);
			free(B11[i]);
			free(B12[i]);
			free(B21[i]);
			free(B22[i]);
			free(C11[i]);
			free(C12[i]);
			free(C21[i]);
			free(C22[i]);
			free(P1[i]);
			free(P2[i]);
			free(P3[i]);
			free(P4[i]);
			free(P5[i]);
			free(P6[i]);
			free(P7[i]);
			free(AResult[i]);
			free(BResult[i]);
		}
		free(A11);
		free(A12);
		free(A21);
		free(A22);
		free(B11);
		free(B12);
		free(B21);
		free(B22);
		free(C11);
		free(C12);
		free(C21);
		free(C22);
		free(P1);
		free(P2);
		free(P3);
		free(P4);
		free(P5);
		free(P6);
		free(P7);
		free(AResult);
		free(BResult);
	}
}

int main() {
	float **a = (float **)malloc(sizeof(float *) * N); 
	float **b = (float **)malloc(sizeof(float *) * N);
	float **c = (float **)malloc(sizeof(float *) * N);
	int i, j;
	clock_t  start, stop;
	//初始化矩阵a,b和c
	for (i = 0; i < N; i++) {
		a[i] = (float *)malloc(sizeof(float) * N);
		b[i] = (float *)malloc(sizeof(float) * N);
		c[i] = (float *)malloc(sizeof(float) * N);
		for (j = 0; j < N; j++)
		{
			a[i][j] = i * 0.02 + j * 0.01;
			b[i][j] = i * 0.01 + j * 0.02;
			c[i][j] = 0.0;
		}
	}
	start = clock();
	matrixMul_base(a, b, c, N);
	stop = clock();
	printf("The time of bsae matrix multiplication:%f\n", (double)(stop - start) / CLOCKS_PER_SEC);
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c[i][j] = 0.0;
	start = clock();
	matrixMul_Strassen(a, b, c, N);
	stop = clock();
	printf("The time of matrix multiplication with Strassen:%f\n", (double)(stop - start) / CLOCKS_PER_SEC);
	return 0;
}
