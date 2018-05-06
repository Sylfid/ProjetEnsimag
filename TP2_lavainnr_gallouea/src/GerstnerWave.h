#include "WaveModel.h"


class GerstnerWave{
    private:
        double phase;
        double amplitude;
        Dvector direction;
        double frequence;
        Dvector positionInit;
    public:
        GerstnerWave();
        GerstnerWave(double phase, double amplitude,
                Dvector direction, double frequence, double x0, double
                y0);
        GerstnerWave(GerstnerWave const& copie);
        ~GerstnerWave();
        GerstnerWave& operator=(const GerstnerWave 
                &copie);
        Dvector operator()(double t) const;

};

