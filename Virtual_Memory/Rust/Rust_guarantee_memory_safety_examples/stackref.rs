fn main() {
    let reference_to_nothing = stackref ();
}

fn stackref () -> &i32 {
    let val:i32 = 10;
    &val
}
