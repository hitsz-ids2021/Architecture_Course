# 演示实验介绍
本目录主要是利用6个扩展的例子来解释说明链接器处理重复符号定义的三条规则可能带来的一些困惑
foo{1...6}.c是包含main的主文件，bar{1...6}.c是定义同名全局符号的辅助文件。
foo1.c和bar1.c：定义两个同名强符号main，造成链接时错误
foo2.c和bar2.c：定义两个同名弱符号x，根据规则三，链接器会随机选择某一个定义，使得这两个文件对符号x的引用都解析到这个定义上去。
foo3.c和bar3.c：同样是两个弱符号，但是由于类型不同，如果链接器符号解析时确定的定义是int x;则，在bar3.c中对double x的赋值操作会覆盖其他内存区域，在这里就是x之后的4个字节。但是，在多台机器上试验，发现链接器往往会选择double x的定义（可以查看可执行文件foobar3的符号表中x的条目信息，若大小为8，即选择了doublex的定义）。
foo4.c和bar4.c：同理，只是这里的int x的定义被初始化了。因此上述情况一定发生
foo5.c和bar5.c：定义了一个强符号int x = 15213;和一个弱符号，利用规则二，在bar5.c中所有对x的引用都会解析到强符号上去。
foo6.c和bar6.c：定义了两个弱符号——结构体类型s的变量s1，只是两个文件中结构体定义的成员变量不同。
```c
/* foo6.c */
typedef struct
{
    int x;
    double y;
}s;
/* bar6.c */
typedef struct
{
    double y;
    int x;
}s;
```
### 编译/运行
```shell
linux > gcc -Wall -Og -o foobar1 foo1.c bar1.c
linux > gcc -Wall -Og -o foobar2 foo2.c bar2.c
linux > gcc -Wall -Og -o foobar3 foo3.c bar3.c show_bytes_b.c
linux > gcc _wall -Og -o foobar4 foo4.c bar4.c show_bytes_b.c
linux > gcc -Wall -Og -o foobar5 foo5.c bar5.c
linux > gcc -Wall -Og -o foobar6 foo6.c bar6.c show_bytes_b.c
```

###Files
show_bytes_b.c 辅助打印模块，按照正常阅读顺序（即高位字节在左，低位字节在右）打印任意字节序列，任意类型的变量，目前支持打印int, float, double, 指针，有需要可以扩展。
test.sh 多次执行编译、运行某个foo.c和bar.c文件，输入第一个参数为想要重复执行的文件名数字，第二个参数为想要循环的次数，如想要循环编译并测试结果10次foo3.c和bar3.c，输入`linux > ./test.sh 3 10`.编译的文件保存在tmp目录下, 结果输出和错误都保存在tmp/results.txt中

### Command
本目录下的命令使用Makefile管理
如需生成所有的文件，直接执行`linux > make all`,但是这里不建议直接生成所有，因为本目录下的所有示例都是为了演示一些puzzles，比如foobar1是设计成会报链接时错误
因此，尽量用`linux > make foobar1`来分别执行
清理所有中间文件，执行`linux > make clean`
GCC 命令可参考Makefile
