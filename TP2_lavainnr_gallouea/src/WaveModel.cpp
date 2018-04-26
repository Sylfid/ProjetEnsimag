#include <exception>
#include <string>
#include <iostream>
#include "WaveModel.h"
#include <cstdlib>



WaveModel::WaveModel(){
    this->wind = new Dvector();
    this->alignment = new Dvector();
    this->intensite = 0;
    this->waveLength = 0;
    this->param = 0;
}

WaveModel::WaveModel(Dvector wind, Dvector alignment,
        double intensite, double waveLenght, double param){
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
    wind = new Dvector(*copie.wind);
    alignment = new Dvector(*copie.alignment);
} 

WaveModel::~WaveModel(){
    std::cout<<"Destructeur WaveModel";
    delete wind;
    delete alignment;
}

WaveModel& WaveModel::operator=(const WaveModel &w){
    wind = w.wind;
    alignment = w.alignment;
    intensite = w.intensite;
    waveLength = w.waveLength;
    param = w.param;
    return *this;
}

double WaveModel::getItensite() const{
    return intensite;
}

double WaveModel::getWaveLength() const{
    return waveLength;
}

double WaveModel::getParam() const{
    return param;
}

Dvector* WaveModel::getWind() const{
    return wind;
}

Dvector* WaveModel::getAlignment() const{
    return alignment;
}
