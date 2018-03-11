struct Puissances {
    suivante: u32,
}

impl Puissances {
    fn new() -> Self {
        Puissances { suivante: 1 }
    }
}

impl Iterator for Puissances {
    type Item = u32;
    fn next(&mut self) -> Option<Self::Item> {
        let courante = self.suivante;
        self.suivante *= 2;
        Some(courante)
    }
}

fn main() {
    for x in Puissances::new().take(5) {
        println!("x: {}", x);
    }
    let racines: Vec<f64> = Puissances::new()
        .take(10)
        .map(|p| (p as f64).sqrt())
        .collect();
    println!("racines: {:?}", racines);
}
