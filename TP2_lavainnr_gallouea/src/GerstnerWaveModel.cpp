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
    std::cout << gerstnerWave.size() << std::endl;
    for(int j(0); j < ny; j ++){
        for(int i(0); i < nx; i ++){
            gerstnerWave[i + j*nx] = new GerstnerWave(0, 5, wind, 0.5, i, j);    
        }
    }
    std::cout << gerstnerWave.size() << std::endl;
}

double GerstnerWaveModel::operator()(int x, int y, int t) const{
    std::cout << gerstnerWave.size() << std::endl;
    return (*gerstnerWave[x + y * nx])(t)(2);
}


