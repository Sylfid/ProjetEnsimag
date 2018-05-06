#include <exception>
#include <string>
#include <iostream>
#include "GerstnerWaveModel.h"
#include <cstdlib>

GerstnerWaveModel::GerstnerWaveModel() : WaveModel(){
    std::vector<GerstnerWave*> gerstnerWave;
}

GerstnerWaveModel::GerstnerWaveModel(Dvector wind, Dvector alignment, 
                double intensite, double waveLen, double param, int nbx, int nby)
                : WaveModel(wind, alignment, intensite, waveLen, param){
    nx = nbx;
    ny = nby;
    gerstnerWave.resize(nx * ny);
    for(int i(0); i < nx; i ++){
        for(int j(0); j < ny; j ++){
            gerstnerWave[i*ny + j] = new GerstnerWave(0, 5, wind, 0.5, i, j);    
        }
    }
}

double GerstnerWaveModel::operator()(int x, int y, int t) const{
    return (*gerstnerWave[x + y * nx])(t)(2);
}


