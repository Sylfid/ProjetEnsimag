#include <exception>
#include <string>
#include <iostream>
#include "WaveModel.h"
#include <cstdlib>



WaveModel::WaveModel(){
    this->wave = new Height();
    this->wind = new Dvector();
    this->alignment = new Dvector();
    this->intensite = 0;
    this->waveLength = 0;
}

WaveModel::WaveModel(Height* wave, Dvector* wind, Dvector* alignment, double intensite,
                double waveLenght){
    this->wave = wave;
    this->wind = wind;
    this->alignment = alignment;
    this->intensite = intensite;
    this->waveLength = waveLenght;
}
 
