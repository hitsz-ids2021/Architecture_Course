## Rust环境搭建
1. 安装Rust
$ curl https://sh.rustup.rs -sSf | sh
2. 将Rust手动添加到系统PATH中：
$ source $HOME/.cargo/env
3. 编写和运行Rust程序
创建main.rs文件写入一下内容：
fn main() {
    println!("Hello, world!");
}
编译
$ rustc main.rs
运行
$ ./main

## Rust实验
要求：在experiment文件夹中有三个存在编译错误的Rust程序experiment1.rs，experiment2.rs，experiment3.rs，在限制条件下修改程序，使它们可以成功编译，并且要保持程序的原有功能。

> experiment1.rs限制条件：不添加任何一行代码，只对原有代码做修改。

> experiment2.rs限制条件：fill_vec函数不能有参数。

> experiment3.rs限制条件：不能删除第7行代码：println!("{} has length {} content `{:?}`", "vec0", vec0.len(), vec0);。

实验报告中要包含修改后的代码以及对所做修改的解释说明。

参考：
https://doc.rust-lang.org/book/ch04-01-what-is-ownership.html
https://doc.rust-lang.org/book/ch04-02-references-and-borrowing.html

## Rust_guarantee_memory_safety_examples文件夹
一些rust的保护内存安全、发现错误的例子