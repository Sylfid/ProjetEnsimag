fn main() {
    let mut v1 = vec![1,2,3,4,5];
    let mut v2 = vec![0;5];
    println!("v2: {:?}", v2);
    for i in 1..6{
        v2[i-1]=i as i32;
    }
    remise_a_zero(v2.as_mut_slice());
    println!("v2: {:?}", v2);
    assert_eq!(v1,v2);
}

fn remise_a_zero(tranche: & mut [i32]) {
    let taille = tranche.len();
    for i in 0..taille{
        tranche[i]=0;
    }
}
        
    
