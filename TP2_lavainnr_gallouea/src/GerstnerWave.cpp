#include <exception>
#include <string>
#include <iostream>
#include "GerstnerWave.h"
#include <cstdlib>
#include <math.h>

GerstnerWave::GerstnerWave():direction(),positionInit(){
    phase=0;
    amplitude=0.0;
    frequence=0.0;
}

GerstnerWave::GerstnerWave(double phase, double amplitude, Dvector 
        direction2, double frequence, double x0, double y0){
    this->phase=phase;
    this->amplitude=amplitude;
    this->frequence=frequence;
    direction=direction2;
    Dvector position(2,0.0);
    position(0)=x0;
    position(1)=y0;
    this->positionInit=position;
}

GerstnerWave::GerstnerWave(GerstnerWave const& copie):
      direction(copie.direction), positionInit(copie.positionInit){
    phase=copie.phase;
    amplitude=copie.amplitude;
    frequence=copie.frequence;
}

GerstnerWave::~GerstnerWave(){
    direction.~Dvector();
    positionInit.~Dvector();
}

GerstnerWave& GerstnerWave::operator=(const GerstnerWave &copie){
    phase=copie.phase;
    amplitude=copie.amplitude;
    direction=copie.direction;
    frequence=copie.frequence;
    positionInit=copie.positionInit;
    return *this;
}

Dvector GerstnerWave::operator()(double t) const{
    Dvector position(3,0.0);
    position(0)=positionInit(0) - (direction(0)/
            direction.abs())*amplitude*sin(direction*positionInit -
            frequence*t + phase);
    position(1)=positionInit(1) - (direction(1)/
            direction.abs())*amplitude*sin(direction*positionInit -
            frequence*t + phase);
    position(2)=amplitude*cos(direction*positionInit - frequence*t
            + phase);
    return position;
}

