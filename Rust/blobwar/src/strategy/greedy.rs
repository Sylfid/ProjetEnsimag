//! Dumb greedy algorithm.
use std::fmt;
use super::Strategy;
use configuration::{Configuration, Movement};

/// Dumb algorithm.
/// Amongst all possible movements return the one which yields the configuration with the best
/// immediate value.
pub struct Greedy();

impl fmt::Display for Greedy {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Greedy")
    }
}

impl Strategy for Greedy {
    fn compute_next_move(&mut self, state: &Configuration) -> Option<Movement> {
        let mut m = None;
        let mut max = -state.value();;
        for mov in state.movements(){
            let val = state.play(&mov).value();
            if val > max {
                max = val;
                m = Some(mov);
            }
        }
        m
    }
}
