> no_leak.rs使用rush语言编写，不存在存泄露。使用rustc no_leak.rs命令编译，编译成功后会生成no_leak可执行文件，使用./no_leak命令可运行。

> stackref.rs使用rush语言编写，存在引用不存在的变量问题。使用rustc stackref.rs命令编译，在编译过程中会检测出该问题，导致编译失败。

> heapref.rs使用rush语言编写，存在引用空闲堆块中的数据问题。使用rustc heapref.rs命令编译，在编译过程中会检测出该问题，导致编译失败。

> off_by_one.rs使用rush语言编写，存在造成错位错误。使用rustc no_leak.rs命令编译，编译成功后会生成off_by_one可执行文件，使用./off_by_one命令可运行。在运行时会发现该错误导致程序退出。
