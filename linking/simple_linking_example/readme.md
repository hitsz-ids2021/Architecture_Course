# 演示实验介绍
本目录利用两个示例程序main.c和sum.c来展示静态链接符号解析和重定位的过程。
sum.c对数组进行求和，并返回结果；main.c初始化数组array，调用sum函数，计算总和 
```c
int sum(int *a, int n)
{
    int i, s = 0;
    
    for (i = 0; i < n; i++) { 
        s += a[i];
    }
    return s;
}
```


首先，我们将两个源文件编译、链接形成可执行目标文件prog
```shell
linux > gcc -Wall -Og -o prog main.c sum.c

```
其次，通过反汇编展示可执行目标文件prog的各个节，来说明ELF目标文件的基本格式，具体内容可查看ELF_Format文件
最后，利用反汇编main.o和prog对应的.text节等信息来说明链接器如何完成重定位步骤。
```shell
linux > objdump -dr sum.o > sumdata-relo.d
linux > objdump -dx -j .data prog > progdata-exe.d
```
### Files
main.c  
sum.c 两个示例程序
ELF_Format 利用反汇编由main.c和sum.c 生成的可执行目标文件prog，展示ELF文件的格式
MakeFile
`linux > make clean; make prog`可以直接生成所有需要的文件，包括prog，以及对main.o、sum.o以及prog反汇编得到的文件

### 
本目录下的所有命令使用Makefile管理
如需生成所有的文件，直接执行`linux > make prog`
清理所有中间文件，执行`linux > make clean`
GCC 命令可参考Makefile
Makefile 使用和介绍，可参见顶层目录readme
