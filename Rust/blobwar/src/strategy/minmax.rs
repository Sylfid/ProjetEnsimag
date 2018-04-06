//! Implementation of the min max algorithm.
use std::fmt;
use super::Strategy;
use configuration::{Configuration, Movement};
use shmem::AtomicMove;

/// Min-Max algorithm with a given recursion depth.
pub struct MinMax(pub u8);

impl Strategy for MinMax {
    fn compute_next_move(&mut self, state: &Configuration) -> Option<Movement> {
       let mut m = None;
       let mut val;
       let mut max = -state.value();
       for mov in state.movements(){
           val = compute_best_move(self.0, state.play(&mov));
           if val > max{
               max = val;
               m = Some(mov);
           }
       }
       m
    }
    
    fn compute_best_move(&mut self, state: &Configuration) -> i8 {
       
       let mut best_move:i8= -state.value();
       let mut other_move:i8=0;
       let mut &Configuration newState;
       for mov in state.movements(){
           newState = state.play(&mov);
           self.0 -=1;
           other_move=self.compute_best_move(newState);
           if best_move < other_move{ 
               best_move=other_move;
           }
           self.0 +=1;
       }
       best_move 
    }
}

impl fmt::Display for MinMax {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Min - Max (max level: {})", self.0)
    }
}

/// Anytime min max algorithm.
/// Any time algorithms will compute until a deadline is hit and the process is killed.
/// They are therefore run in another process and communicate through shared memory.
/// This function is intended to be called from blobwar_iterative_deepening.
pub fn min_max_anytime(state: &Configuration) {
    let mut movement = AtomicMove::connect().expect("failed connecting to shmem");
    for depth in 1..100 {
        movement.store(MinMax(depth).compute_next_move(state));
    }
}
