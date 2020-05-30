## 目录说明
linking目录为计算机体系结构课程**链接**部分的演示实验目录，包含simple_linking_example, symbol_resolution_exercise, duplicate_symbol_names_example, example_static_and_dynamic_linking,library_interpositioning_demo五个演示实验。
每个实验目录下包含所有用到的源代码，以及相应的readme介绍和Makefile文件（包含所有的编译、运行命令）

## 文件格式说明
.c      c源文件
.h      c头文件
.s      编译器生成的汇编语言文件
.o      编译器生成的目标文件
可执行目标文件      一般无后缀，且名字易理解
.a      库文件/存档文件
.so     共享目标文件/动态链接库
.d      反汇编生成的文件

## Make工具介绍
这里为了方便后面对Makefile文件的阅读，简单介绍make工具及Makefile文件：
Linux开发常使用make工具构建大型程序，在命令行中输入`make`，将调用make工具在当前目录下查找Makefile文件并执行，其中Makefile主要记录构建过程中的依赖以及构建命令。
Makefile 的命令主要采用如下形式

```
target: pre
    command1
    command2
```
目标target依赖于pre文件，生成target文件需要执行之后的command1,2...
如果使用`make target`，make工具将会去查找当前目录下是否有target, pre这些文件，以及这些文件是否是最新的，如果发现依赖的文件中有更新或修改，则会重新生成文件target。另外，Makefile也可以定义伪目标，即它不是一个真正的我们需要的文件，而可以是某种操作，比如清除所有中间生成的文件等，详细信息，自行搜索。

### Makefile 基本语法
```make
CC = gcc # 定义将要使用的编译工具是gcc
CFLAGS = -Wall -Og #定义将采用的gcc命令行标志有-Wall -Og

prog: main.o sum.o #说明prog文件的生成依赖于main.o和sum.o，如果没有这两个文件，make会先去找是否有这两个目标的依赖，而在这里我们可以省略.o目标的定义如`main.o: main.c`，make工具会自动完成main.o的编译
$(CC) $(CFLAGS) -o prog main.o sum.o #这就是一条gcc编译指令，只是使用了在之前定义的变量 CC和CFLAGS

clean: 
rm -rf *.o *.s *.a *.so   #定义了一个伪目标，这个伪目标没有任何依赖，需要执行rm操作
    
```
