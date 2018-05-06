#ifndef GERSTNERWAVEMODEL_H
#define GERSTNERWAVEMODEL_H

#include "GerstnerWave.h"
#include <vector>

class GerstnerWaveModel : public WaveModel{
    private:
        std::vector<GerstnerWave*> gerstnerWave;
        int nx;
        int ny;
    public:
        double operator()(int x, int y, int t) const;
        GerstnerWaveModel();
        GerstnerWaveModel(Dvector wind, Dvector alignment, 
                double intensite, double waveLenght, double param, int nx, int ny);
        ~GerstnerWaveModel();
};

#endif
