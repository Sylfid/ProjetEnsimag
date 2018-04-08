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
       let mut val:i8;
       let mut max = compute_best_move(self.0, &state.skip_play(),state.current_player);
       for mov in state.movements(){
           val = compute_best_move(self.0, &state.play(&mov), state.current_player);
           if val > max{
               max = val;
               m = Some(mov);
           }
       }
       m
    }
    
}

impl fmt::Display for MinMax {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Min - Max (max level: {})", self.0)
    }
}

fn compute_best_move(depth: u8, state: &Configuration, player: bool) -> i8 {
    let mut a:i8;
    let mut b:i8;
   if(state.current_player){
       a=state.value();
   }
   else{
       a=-state.value();
   }
   if (player) {
       a = a*-1;
   }
   if (depth as u8) == 0{
       a
   }
   else{
       let mut flag=false;
       let mut other_move:i8;
       let mut new_state;
       new_state=state.skip_play();
       let mut best_move:i8 = compute_best_move(depth-1,&new_state,player); 
       for mov in state.movements(){
           flag=true;
           new_state = state.play(&mov);
           other_move=compute_best_move(depth-1, &new_state, player);
           if(!state.current_player ^ player){
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
       if (!flag){
           a
       }
       else{
           best_move
       }
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
