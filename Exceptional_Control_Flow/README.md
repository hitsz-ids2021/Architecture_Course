# 本页面中包含异常控制流PPT中所涉及的代码，PPT中已经标注好文件名，可根据文件名进行查找

 fork1.c:一个fork实例
> 1. 编译：gcc -o fork1 fork1.c -lpthread
> 2. 运行：./fork1

 fork2.c:另一个fork实例，并且用到atexit函数（添加一个函数到函数列表，在调用exit后调用该函数。
> 1. 编译：gcc -o fork2 fork2.c -lpthread
> 2. 运行：./fork2

 waitpid.c:一个waitpid的实例
> 1. 编译：gcc -o waitpid waitpid.c -lpthread
> 2. 运行：./waitpid

 signal.c:包含了fork、waitpid、signal、sigprocmask的一个实例
> 1. 编译：gcc -o signal signal.c -lpthread
> 2. 运行：./signal

 counter.c:展示signal不会排队的一个实例
> 1. 编译：gcc -o counter counter.c -lpthread
> 2. 运行：./counter

 concurrency_buggy.c:有并发错误的一个实例
> 1. 编译：gcc -o concurrency_buggy concurrency_buggy.c -lpthread
> 2. 运行：./concurrency_buggy

 concurrency.c:同步流解决了上一个程序并发错误
> 1. 编译：gcc -o concurrency concurrency.c -lpthread
> 2. 运行：./concurrency

 waitforsignal.c:利用循环显示地去等待一个信号
> 1. 编译：gcc -o waitforsignal waitforsignal.c -lpthread
> 2. 运行：./waitforsignal

 sigsuspend.c:上一个循环太浪费，此程序利用sigsuspend来显示地等待信号
>1. 编译：gcc -o sigsuspend sigsuspend.c -lpthread
>2. 运行：./sigsuspend

 setjmp.c:利用非本地跳转从一个深层嵌套的函数调用中立即返回
> 1. 编译：gcc -o setjmp setjmp.c -lpthread
> 2. 运行：./setjmp

 restart.c:利用非本地跳转使信号处理程序分支到一个特殊的代码位置
> 1. 编译：gcc -o restart restart.c -lpthread
> 2. 运行：./restart

注：
如果是刚装好的gcc不能编译，则是因为没有一些必须的头文件，现在需要安装build-essential，安装了这个包会安装上g++、libc6-dev、linux-libc-dev等好多必须的软件和头文件。
更新资源地址：sudo apt-get update
安装build-essential：sudo apt-get install build-essential
