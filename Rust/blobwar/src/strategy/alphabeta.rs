//! Alpha - Beta algorithm.
use std::fmt;

use super::Strategy;
use configuration::{Configuration, Movement};
use shmem::AtomicMove;

/// Anytime alpha beta algorithm.
/// Any time algorithms will compute until a deadline is hit and the process is killed.
/// They are therefore run in another process and communicate through shared memory.
/// This function is intended to be called from blobwar_iterative_deepening.
pub fn alpha_beta_anytime(state: &Configuration) {
    let mut movement = AtomicMove::connect().expect("failed connecting to shmem");
    for depth in 1..100 {
        let chosen_movement = AlphaBeta(depth).compute_next_move(state);
        movement.store(chosen_movement);
    }
}

/// Alpha - Beta algorithm with given maximum number of recursions.
pub struct AlphaBeta(pub u8);

impl fmt::Display for AlphaBeta {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Alpha - Beta (max level: {})", self.0)
    }
}

impl Strategy for AlphaBeta {
    fn compute_next_move(&mut self, state: &Configuration) -> Option<Movement> {
        
       let mut m = None;
       let mut val:i8;
       let mut max = compute_best_move(self.0, &state.skip_play(),state.current_player, -128, 127);
       for mov in state.movements(){
           val = compute_best_move(self.0, &state.play(&mov), state.current_player, -128, 127);
           if val >= max{
               max = val;
               m = Some(mov);
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
    if (state.current_player) ^ player {
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
           beta2=min(alpha2,v);
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
