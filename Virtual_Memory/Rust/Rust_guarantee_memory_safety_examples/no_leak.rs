fn func() {
    let mut a = Box::new(5);
    *a = 10;
}

fn main() {
    func();
}
