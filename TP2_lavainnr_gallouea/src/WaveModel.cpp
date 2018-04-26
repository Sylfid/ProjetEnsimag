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
    this->param = 0;
}

WaveModel::WaveModel(Height wave, Dvector wind, Dvector alignment,
        double intensite, double waveLenght, double param){
    this->wave = new Height(wave);
    this->wind = new Dvector(wind);
    this->alignment = new Dvector(alignment);
    this->intensite = intensite;
    this->waveLength = waveLenght;
    this->param = param;

}

WaveModel::WaveModel(WaveModel const& copie){
    intensite=copie.intensite;
    waveLength = copie.waveLength;
    param = copie.param;
    wave = new Height(*copie.wave);
    wind = new Dvector(*copie.wind);
    alignment = new Dvector(*copie.alignment);
} 

WaveModel::~WaveModel(){
    std::cout<<"Destructeur WaveModel";
    delete wave;
    delete wind;
    delete alignment;
}

WaveModel& WaveModel::operator=(const WaveModel &w){
    wave = w.wave;
    wind = w.wind;
    alignment = w.alignment;
    intensite = w.intensite;
    waveLength = w.waveLength;
    param = w.param;
    return *this;
}
