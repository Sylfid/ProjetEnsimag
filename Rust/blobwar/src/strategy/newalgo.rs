//! NewAlgo algorithm.
use std::fmt;
use super::Strategy;
use configuration::{Configuration, Movement};
use shmem::AtomicMove;

/// NewAlgo algorithm with given maximum number of recursions.
pub struct NewAlgo(pub u8);

impl fmt::Display for NewAlgo{
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "NewAlgo (max level: {})", self.0)
    }
}

/// Anytime alpha beta algorithm.
/// Any time algorithms will compute until a deadline is hit and the process is killed.
/// They are therefore run in another process and communicate through shared memory.
/// This function is intended to be called from blobwar_iterative_deepening.
pub fn new_algo_anytime(state: &Configuration) {
    let mut movement = AtomicMove::connect().expect("failed connecting to shmem");
    for depth in 1..100 {
        movement.store(NewAlgo(depth).compute_next_move(state));
    }
}
impl Strategy for NewAlgo{
    fn compute_next_move(&mut self, state: &Configuration) -> Option<Movement> {
        
       let mut m = None;
       let mut val:i8;
       let mut max = compute_best_move(self.0,1, &state.skip_play(),state.current_player);
       let mut new_state;
       for mov in state.movements(){
           new_state=state.play(&mov);
           if abs(state.value()+new_state.value())>0{
               val = compute_best_move(self.0,1, &new_state, state.current_player);
               if val >= max{
                   max = val;
                   m = Some(mov);
               }
           }
       }
       m
    }
}

fn compute_best_move(depth: u8, actualdepth: u8, state: &Configuration, player: bool)
                    -> i8 {
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
    let mut new_state;
    let mut best_move:i8 = compute_best_move(depth-1,actualdepth+1,&state.skip_play(),player); 
    let mut other_move;
    let mut flag = false;
    for mov in state.movements(){
        flag=true;
        new_state = state.play(&mov);
        let mut a=0;
        if abs(state.value()+new_state.value())>2 && actualdepth < 3{
            a=1;
        }
        other_move=compute_best_move(depth-1+a,actualdepth+1, &new_state,player);
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

fn abs(arg1: i8) -> i8{
    if arg1<0 {
        -arg1
    }
    else{
        arg1
    }
}
