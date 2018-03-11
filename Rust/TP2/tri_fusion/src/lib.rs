extern crate itertools;
extern crate rand;
use itertools::{kmerge, repeat_call};
use std::mem::swap;

/// Renvoie un vecteur de u32 aleatoire (valeurs comprises entre 0 et 99) de la taille donnee.
pub fn vecteur_aleatoire(taille: usize) -> Vec<u32> {
    repeat_call(|| rand::random::<u32>() % 100)
        .take(taille)
        .collect()
}

/// Remplit la tranche par 'taille' zeros puis 'taille' uns, ...
/// # Example:
/// ```
/// use tri_fusion::remplir_blocs;
/// let mut tableau = [0; 5];
/// remplir_blocs(&mut tableau, 1);
/// assert_eq!(tableau, [0, 1, 2, 3, 4]);
/// remplir_blocs(&mut tableau, 2);
/// assert_eq!(tableau, [0, 0, 1, 1, 2]);
/// remplir_blocs(&mut tableau, 3);
/// assert_eq!(tableau, [0, 0, 0, 1, 1]);
/// ```
pub fn remplir_blocs(tranche: &mut [u32], taille: usize) {
    //tranche.chunks_mut(taille).enumerate().map(|(i,x)| x.iter_mut().map(|y| *y=(i as u32)));
    for (i, tableau) in tranche.chunks_mut(taille).enumerate(){
        for j in tableau.iter_mut(){
            *j= i as u32;
        }
    }
}

// Fusionne les tableaux de taille `taille_blocs` contenus dans s dans d.
// Pre-condition: tous les sous-tableaux de taille `taille_blocs` sont tries.
// # Example:
// ```
// use tri_fusion::fusion;
// let source = [0,4,2,3];
// let mut destination = [0,0,0,0];
// fusion(&source, &mut destination, 2);
// assert_eq!(destination, [0,2,3,4]);
// let source = [0,4,5,2,3];
// let mut destination = [0,0,0,0,0];
// fusion(&source, &mut destination, 3);
// assert_eq!(destination, [0,2,3,4,5]);
// let source = [3];
// let mut destination = [0];
// fusion(&source, &mut destination, 1);
// assert_eq!(destination, [3]);
// ```
pub fn fusion(s: &[u32], d: &mut [u32], taille_blocs: usize) {
       for (si, di) in kmerge(s.chunks(taille_blocs)).zip(d.iter_mut()){
           *di=*si;
       }
}


/// Tri fusion iteratif
/// # Example:
/// ```
/// use tri_fusion::{vecteur_aleatoire, tri_fusion};
/// let mut v = vecteur_aleatoire(1000);
/// let mut w = v.clone();
/// v.sort();
/// tri_fusion(&mut w);
/// assert_eq!(v, w);
/// ```
pub fn tri_fusion(tranche: &mut [u32]) {
    if tranche.len()>1{
        let taille = ((tranche.len()+1)/2);
        let mut copie=Vec::new();
        for i in tranche.iter(){
            copie.push(0); 
        } 
        for x in tranche.chunks_mut(taille){
            tri_fusion(x);
        }
        fusion(tranche, &mut copie[..],taille);
        tranche.clone_from_slice(&copie[..]);
    }

}

