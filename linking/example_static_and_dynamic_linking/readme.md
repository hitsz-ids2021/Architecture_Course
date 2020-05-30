# 演示实验介绍
本目录为有关静态链接和动态链接的演示目录，其中包括利用静态链接库进行链接，加载时动态链接和运行时动态链接三个演示实验

1. 链接静态链接库
```shell
linux > gcc -Wall -Og -c  main2.c addvec.c multvec.c
linux > ar rcs libvector.a addvec.o multvec.o
linux > gcc -Wall -Og -static -o prog2c main2.o libvector.a
##或者是使用下面这条语句
linux > gcc -Wall -Og -static -o prog2c main2.o -L. -lvector
```
2. 加载时动态链接
```shell
## -shared 指示链接器生成一个共享目标文件， -fpic 告诉链接器生成位置无关代码
linux > gcc -Wall -Og -shared -fpic -o libvector.so addec.c multvec.c
linux > gcc -Wall -Og -o prog2l main2.o ./libvector.so
```
3. 运行时动态链接
```shell
## -rdynamic  通知链接器将所有符号添加到动态符号表中，使得之后可以使用类似于dlopen这类接口查询到符号，-ldl 指定程序需要链接动态函数库，在编译使用动态链接库的程序都需要加入这两个编译选项 
linux > gcc -Wall -Og -rdynamic -o prog2r dll.c -ldl
```

### Files
addvec.c 包含向量的加法操作  
multvec.c 包含向量的对应元素乘法  
main2.c 初始化数组array，并使用addvec函数做加法运算  
vector.h 包含addvec和multvec的函数声明的头文件  
dll.c 运行时动态链接的演示源程序,  使用dlopen加载链接需要的动态链接库，使用dlsym接口找到需要的符号位置   
Makefile  

### Command
本目录下的命令使用Makefile管理  
如需生成所有的文件，直接执行`linux > make all`  
清理所有中间文件，执行`linux > make clean`  
GCC 命令可参考Makefile  