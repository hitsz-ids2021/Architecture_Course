fn main() {
    {
        let mut a = Box::new(5);
        println!("{}", *a);
    }
    println!("{}", *a);
}
