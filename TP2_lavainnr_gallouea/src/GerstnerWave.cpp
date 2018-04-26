#include <exception>
#include <string>
#include <iostream>
#include "GerstnerWave.h"
#include <cstdlib>

GerstnerWave::GerstnerWave(){
    phase=0;
    amplitude=0.0;
    frequence=0.0;
    direction = new Dvector();
}

GerstnerWave::GerstnerWave(double phase, double amplitude, Dvector 
        direction, double frequence){
    this->phase=phase;
    this->amplitude=amplitude;
    this->direction= new Dvector(direction);
    this->frequence=frequence;
}

GerstnerWave::GerstnerWave(GerstnerWave const& copie){
    phase=copie.phase;
    amplitude=copie.amplitude;
    direction = new Dvector(*copie.direction);
    frequence=copie.frequence;
}

GerstnerWave::~GerstnerWave(){
    delete direction;
}

GerstnerWave& GerstnerWave::operator=(const GerstnerWave &copie){
    phase=copie.phase;
    amplitude=copie.amplitude;
    *direction=*copie.direction;
    frequence=copie.frequence;
}
