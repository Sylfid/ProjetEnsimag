fn main() {
    let r:Vec<i32>= (1..21).into_iter().collect();
    let s:Vec<i32>= (1..21).into_iter().rev().collect();
    let t:Vec<i32>=r.iter().zip(s.iter()).map(|(x,y)| *x + *y).collect();
    if !t.iter().all(|x| *x==21){
        println!("Le résultat est faux !");
    }
    println!("r : {:?}", r);
    println!("s : {:?}", s);
    println!("t : {:?}", t);
    let x:i32 = r.iter().sum();
    println!("x : {:?}", x);
    let u:Vec<i32>=(1..11).into_iter().map(|x| x * x).collect();
    println!("u : {:?}", u);
}
