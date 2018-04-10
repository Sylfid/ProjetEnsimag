//! Min-Max-Proba algorithm.
use std::fmt;
use std::iter::IntoIterator;
use super::Strategy;
use configuration::{Configuration, Movement};
use shmem::AtomicMove;
use rand::{thread_rng, Rng};
//use rand::Rng;
//use rand::{task_rng, Rng};

/// Anytime Min Max Proba algorithm.
/// Any time algorithms will compute until a deadline is hit and the process is killed.
/// They are therefore run in another process and communicate through shared memory.
/// This function is intended to be called from blobwar_iterative_deepening.
pub fn min_max_proba_anytime(state: &Configuration) {
    let mut movement = AtomicMove::connect().expect("failed connecting to shmem");
    for depth in 1..100 {
        let chosen_movement = MinMaxProba(depth).compute_next_move(state);
        movement.store(chosen_movement);
    }
}

/// Min_Max_Proba algorithm with given maximum number of recursions.
pub struct MinMaxProba(pub u8);

impl fmt::Display for MinMaxProba {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Min - Max - Proba (max level: {})", self.0)
    }
}

impl Strategy for MinMaxProba {
    fn compute_next_move(&mut self, state: &Configuration) -> Option<Movement> {
        
       let mut m = None;
       let mut val:i8;
       let mut max = compute_best_move(self.0, &state.skip_play(),state.current_player,0);
       let mut new_state;
       for mov in state.movements(){
           new_state= state.play(&mov);
           if abs(state.value()+new_state.value())>0{
               val = compute_best_move(self.0, &new_state , state.current_player,0);
               if val >= max{
                   max = val;
                   m = Some(mov);
               }
           }
       }
       m
    }
}

fn compute_best_move(depth: u8, state: &Configuration, 
                     player: bool, seuil:i8) -> i8 {
    let mut a:i8;
    if state.current_player {
       a=state.value();
    }
    else{
       a=-state.value();
    }
    if player {
       a = -a;
    }
    if (depth as u8) == 0{
       return a
    }
    let mut flag = false;
    let mut other_move;
    let mut best_move=compute_best_move(depth-1, &state.skip_play(),
    player,seuil);
    let mut new_state;
    let mut compteur:i8=0;
    let mut compteur2:i8=seuil;
    let mut flag2=false;
    for mov in state.movements(){//echantillon{
        flag=true;
        new_state = state.play(&mov);
        if abs(new_state.value()+state.value())>0+compteur2 {
            flag2=true;
            compteur=compteur+1;
            if compteur < 3{
                compteur=0;
                if compteur2 < 6{
                    compteur2=compteur2+1;
                }
            }
            other_move=compute_best_move(depth-1, &new_state, player, compteur2);
            if !state.current_player ^ player {
               if best_move < other_move{ 
                   best_move=other_move;
               }
            }
            else{
               if best_move > other_move{ 
                   best_move=other_move;
               }
            }
        }
    }
    if flag2==false && seuil!=0{
        compute_best_move(depth,&state,player,0)
    }
    else{
        if !flag {
           if state.current_player^player{
               127
           }
           else{
               -127
           }
        }
        else{
           best_move
        }
    }
    
}

fn abs(arg1: i8) -> i8{
    if arg1<0 {
        -arg1
    }
    else{
        arg1
    }
}
