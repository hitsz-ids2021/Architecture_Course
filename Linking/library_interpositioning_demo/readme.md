# 演示实验介绍 
本目录主要展示三种强大的打桩机制：包括编译时打桩，链接时打桩，加载/运行时打桩用于截获和包装库函数调用,如malloc、free。
实验目标是截获对malloc和free的调用以追踪它们分配和释放的内存块的大小及地址。
1. 编译时打桩
主要是利用预处理器的宏展开技术，我们定义了一个malloc.h利用宏将malloc展开成我们的包装函数mymalloc，并且保持它们的原型一致，然后我们利用-I.编译参数指示编译驱动程序从当前目录include头文件，从而达到截获调用的目的。
```c
/* malloc.h */
#define malloc(size) mymalloc(size)
#define free(ptr) myfree(ptr)

void *mymalloc(size_t size);
void myfree(void *ptr);


/* mymallo.c compile time wrapper function*/
void *mymalloc(size_t size)
{
    void *ptr = malloc(size); 
    printf("malloc(%d)=%p\n", 
           (int)size, ptr); 
    return ptr;
} 
```

2. 链接时打桩
利用链接器的符号解析功能，传入参数-Wl, wrap, malloc 使得链接器在解析符号时，将符号malloc解析成__wrap_malloc，而将符号__real_malloc解析到malloc上。然后定义我们的包装函数为__wrap_malloc，并且在包装函数内部需要调用malloc时, 使用__real_malloc，同样可以截获调用

```c
/* mymalloc.c linktime wrapper funtion
void *__real_malloc(size_t size);

/* malloc wrapper function */
void *__wrap_malloc(size_t size)
{
    void *ptr = __real_malloc(size); /* Call libc malloc */
    printf("malloc(%d) = %p\n", (int)size, ptr);
    return ptr;
}
```

3. 加载/运行时打桩
加载/运行时打桩技术主要使用动态链接器的环境变量技术，在运行时设置环境变量LD_PRELOAD为你实现已经编译好的包含包装程序的动态链接库所在的路径，使得在加载运行时如果动态链接器遇到没有解析的符号会首先去LD_PRELOAD所指向的路径下查找。这样也达到了截获库函数调用的目的。
```c
void *malloc(size_t size)
{
    void *(*mallocp)(size_t size);
    char *error;

    mallocp = dlsym(RTLD_NEXT, "malloc"); /* Get address of libc malloc */
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }
    char *ptr = mallocp(size); /* Call libc malloc */
    printf("malloc(%d) = %p\n", (int)size, ptr);
    return ptr;
}
```

### File
int.c 想要追踪的源程序
mallo.h 编译时打桩使用的头文件
mymalloc.c 三次打桩共用的源文件，通过编译时传入变量`-Dxx`的形式来控制编译的内容

intc       编译时打桩生成的可执行目标文件                                                                                                                                

intl        链接时打桩生成的可执行目标文件                                                                                                                                    

intr       运行时打桩生成的可执行目标文件

### Command
1. 编译时打桩 

  make命令

  编译： make intc
  运行: make runc

  也可以使用gcc命令

  ```shell
  linux > gcc -Wall -Og -DCOMPILETIME -c mymalloc.c
  linux > gcc -Wall -Og -I. -o intc int.c mymalloc.o
  
  运行
  	./intc
  ```

  

2. 链接时打桩

  make命令：

  编译: make intl
  运行: make runl

  gcc命令：

  ```shell
  linux > gcc -Wall -Og -DLINKTIME -c mymalloc.c
  linux > gcc -Wall -Og-c int.c
  linux > gcc -Wall -Og -Wl,--wrap,malloc -Wl,--wrap,free -o intl int.o mymalloc.o
  
  运行:
  	./intl
  ```

  

3. 加载/运行时打桩

  make命令：

  编译: make intr
  运行: make runr

  gcc命令：

  ```shell
  linux > gcc -Wall -Og -DRUNTIME -shared -fpic -o mymalloc.so mymalloc.c -ldl
  linux > gcc -Wall -Og -g -o intr int.c 
  
  运行 
      bash:
  	(LD_PRELOAD="./mymalloc.so" ./intr)	
  ```

  

如需生成所有文件直接执行`linux > make all`
清理所有中间文件，执行`linux > make clean`
具体的GCC命令可以参考Makefile
