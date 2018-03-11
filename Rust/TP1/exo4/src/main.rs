struct Puissances {
    suivante: u32
}
impl Puissances {
    fn new() -> Self {
        Puissances {suivante: 1}
    }
}
impl Iterator for Puissances {
    type Item=u32;
    fn next(&mut self) -> Option<Self::Item> {
        let a = self.suivante;
        self.suivante*=2;
        println!("next Iterator de Puissance");
        Some(a)
    }
}
fn main() {
    let mut a:f64;
    for x in Puissances::new().take(10){
        a=(x as f64).sqrt();
        println!("a: {}", a);
    }
}
