# 矩阵乘法示例

1. flost_matrix_multiplication_SIMD.c是使用SIMD指令对flost类型的矩阵进行矩阵乘法的代码
> 使用gcc -mavx -o flost_matrix_multiplication_SIMD.out flost_matrix_multiplication_SIMD.c进行编译；
2. double_matrix_multiplication_SIMD.c是使用SIMD指令对double类型的矩阵进行矩阵乘法的代码
> 使用gcc -mavx -o double_matrix_multiplication_SIMD.out double_matrix_multiplication_SIMD.c进行编译；
3. matrix_multiplication_Strassen.c是使用Strassen算法进行矩阵乘法的代码
> 使用gcc -o matrix_multiplication_Strassen.out matrix_multiplication_Strassen.c进行编译；
4. matrix_multiplication_optimization.c是case study中对矩阵乘法进行优化的代码
> 使用gcc -mavx -o matrix_multiplication_optimization.out matrix_multiplication_optimization.c进行编译；