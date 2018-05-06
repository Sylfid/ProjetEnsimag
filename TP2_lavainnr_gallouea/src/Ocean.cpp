#include "Ocean.h"
#include "GerstnerWaveModel.h"
#include <iostream>
#include <string>

Ocean::Ocean(double lenx, double leny, int numx, int numy){
    nx = numx;
    ny = numy;
    lx = lenx;
    ly = leny;
    t = 0;
    h = new Height(nx, ny);
    Dvector vent(2,1);
    Dvector align(2, 0);
    model = new GerstnerWaveModel(vent, align, 5, 10, 0, nx, ny);
}

Ocean::~Ocean(){
}

void Ocean::increaseTime(){
    t += 1;
}

void Ocean::computeHeight(){
    //std::cout << h.getTaillex(0) << std::endl;
    //std::cout << h.getTailley() << std::endl;
    for(int i(0); i < nx; i ++){
        for(int j(0); j < ny; j ++){
            (*h)(i, j) = (*model)(i, j, t);
        }
    }
}

void Ocean::display(){
    (*h).display(std::cout);
}
