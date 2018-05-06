#include "GerstnerWave.h"
#include <vector>

class GerstnerWaveModel : public WaveModel{
    private:
        GerstnerWave** gerstnerWave;
        int taille;
    public:
        double operator()(int x, int y, int t) const;
        GerstnerWaveModel();
        GerstnerWaveModel(Dvector wind, Dvector alignment, 
                double intensite, double waveLenght, double 
                param, double phase, double amplitude, double 
                frequence, int taille);
        GerstnerWaveModel(GerstnerWaveModel const& copie);
        ~GerstnerWaveModel();
        GerstnerWaveModel& operator=(GerstnerWaveModel const& copie);
        double operator()(int x, int y, int t) const;
};
