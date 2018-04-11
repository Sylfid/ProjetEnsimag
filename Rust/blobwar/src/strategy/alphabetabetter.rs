//! Alpha - Beta - Better algorithm.
use std::fmt;

use super::Strategy;
use configuration::{Configuration, Movement};
use shmem::AtomicMove;

/// Anytime alpha beta better algorithm.
/// Any time algorithms will compute until a deadline is hit and the process is killed.
/// They are therefore run in another process and communicate through shared memory.
/// This function is intended to be called from blobwar_iterative_deepening.
pub fn alpha_beta_better_anytime(state: &Configuration) {
    let mut movement = AtomicMove::connect().expect("failed connecting to shmem");
    for depth in 1..100 {
        let chosen_movement = AlphaBetaBetter(depth).compute_next_move(state);
        movement.store(chosen_movement);
    }
}

/// Alpha - Beta - Better algorithm with given maximum number of recursions.
pub struct AlphaBetaBetter(pub u8);

impl fmt::Display for AlphaBetaBetter {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Alpha - Beta - Better (max level: {})", self.0)
    }
}

impl Strategy for AlphaBetaBetter {
    fn compute_next_move(&mut self, state: &Configuration) -> Option<Movement> {
        
       let mut m = None;
       let mut val:i8;
       let mut max = compute_best_move(self.0, &state.skip_play(),state.current_player, -100, 100);
       let mut new_state;
       for mov in state.movements(){
           new_state=state.play(&mov);
           if abs(state.value()+new_state.value())>0{
               val = compute_best_move(self.0, &new_state, state.current_player, -100, 100);
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
                     player: bool, alpha: i8, beta: i8) -> i8 {
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
       //return state.value()
    }
    let mut alpha2 = alpha;
    let mut beta2 = beta;
    let mut new_state;
    if (!state.current_player) ^ player {
       let mut v:i8=-100;
       for mov in state.movements(){
           new_state = state.play(&mov);
           v = max(v,compute_best_move(depth-1, &new_state,
                                   player, alpha2, beta2));
           if v > beta2{
               return v
           }
           alpha2=max(alpha2,v);
       }
       v
    }
    else{
       let mut v:i8=100;
       for mov in state.movements(){
           new_state = state.play(&mov);
           v = min(v,compute_best_move(depth-1, &new_state,
                                   player, alpha2, beta2));
           if v < alpha2{
               return v
           }
           beta2=min(beta2,v);
       }
       v
    }
   
}

fn min(arg1: i8, arg2: i8) -> i8{
    if arg1 < arg2{
        arg1
    }
    else{
        arg2
    }
}

fn max(arg1: i8, arg2: i8) -> i8{
    if arg1 < arg2{
        arg2
    }
    else{
        arg1
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
