#[derive(Debug)]
enum Couleur {
Rouge,
Vert,
Bleu,
}

#[derive(Debug)]
struct Point {
x: f64,
y: f64,
couleur: Option<Couleur>,
}

impl Point{
    fn new(s: f64, t: f64)->Self{
        Point{x:s,y:t,couleur:None}
    }
    fn dist(&self, a: Point)->f64{
        ((self.x - a.x).powi(2)+(self.y - a.y).powi(2)).sqrt()
    }
}

fn main() {
    let le_point = Point{
        x:0.0,
        y:0.0,
        couleur:Some(Couleur::Rouge),
    };
}
