#ifndef WAVEMODEL_H
#define WAVEMODEL_H

#include <string>
#include "Height.h"


class WaveModel{
    private:
        Dvector* wind;
        Dvector* alignment;
        double intensite;
        double waveLength;
        double param;
    public:
        WaveModel();
        WaveModel(Dvector wind, Dvector alignment, 
                double intensite, double waveLenght, double param) ;
        WaveModel(WaveModel const& copie);
        ~WaveModel();
        WaveModel& operator=(const WaveModel &w);
        void display(std::ostream& str) const;
        virtual double operator()(int x, int y, int t) const = 0;
        double getItensite() const;
        double getWaveLength() const;
        double getParam() const;
        Dvector* getWind() const;
        Dvector* getAlignment() const;

};

#endif
