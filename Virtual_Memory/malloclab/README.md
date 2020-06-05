***********
主要的文件:
***********

mm.{c,h}	
	实现动态内存分配器的函数头文件及定义文件

mdriver.c	
	malloc测试驱动程序：用来测试编写的mm.c文件（本实验给出了隐式链表mm_implicit.c，显示链表mm_explicit.c,分离的空闲链表mm_segerated.c）

short{1,2}-bal.rep
	两个小的测试跟踪文件帮助你快速开始
traces
	更复杂的测试跟踪文件用于评测

Makefile	
	构建mdrvier

**********************************
其他的支持mdriver的程序
**********************************

config.h	动态内存分配实验的相关配置
fsecs.{c,h}	不同计时器包的包装函数
clock.{c,h}	访问Pentium 和 Alpha 循环计数器的例行程序
fcyc.{c,h}	基于循环计数器的计时器功能
ftimer.{c,h}	基于间隔计时器和gettimeofday（）的计时器函数
memlib.{c,h}	对堆和sbrk函数建模

*******************************
构建并运行driver
*******************************
要构建mdriver，请在对应路径的shell中输入“make”

在一个小的测试跟踪文件上运行mdriver:

	unix> mdriver -V -f short1-bal.rep

-V选项打印出有用的跟踪和摘要信息。

获得mdriver的参数列表：

	unix> mdriver -h

