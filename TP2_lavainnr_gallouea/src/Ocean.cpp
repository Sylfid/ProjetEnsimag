#include "Ocean.h"
#include <iostream>
#include <string>
#include <math.h>

Ocean::Ocean(double lenx, double leny, int numx, int numy, WaveModel* mod){
    nx = numx;
    ny = numy;
    lx = lenx;
    ly = leny;
    t = 0;
    h = new Height(nx, ny);
    Dvector vent(2,1);
    Dvector align(2, 0);
    model = mod; 
}

Ocean::~Ocean(){
}

void Ocean::increaseTime(){
    t += 1;
}

void Ocean::computeHeight(){
    for(int i(0); i < nx; i ++){
        for(int j(0); j < ny; j ++){
            (*h)(i, j) = (*model)(i, j, t);
        }
    }
}

void Ocean::display(){
    (*h).display(std::cout);
}

Ocean::Ocean(Ocean const& copie){
    nx=copie.nx;
    ny=copie.ny;
    lx=copie.lx;
    ly=copie.ly;
    t=copie.t;
    h= new Height(*copie.h);
    *model = *copie.model;
}

Ocean& Ocean::operator=(Ocean const& copie){
    nx=copie.nx;
    ny=copie.ny;
    lx=copie.lx;
    ly=copie.ly;
    t=copie.t;
    *h=*copie.h;
    *model = *copie.model;
    return *this;
}

