#include <exception>
#include <string>
#include <iostream>
#include "GerstnerWaveModel.h"
#include <cstdlib>

GerstnerWaveModel::GerstnerWaveModel() : WaveModel(){
    gerstnerWave=NULL;
}

GerstnerWaveModel::GerstnerWaveModel(Dvector wind, Dvector alignment, 
                double intensite, double waveLenght, double param,
                double phase, ) ;

