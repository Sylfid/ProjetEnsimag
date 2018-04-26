#include "WaveModel.h"

class GerstnerWave{
    private:
        double phase;
        double amplitude;
        Dvector* direction;
        double frequence;
    public:
        GerstnerWave();
        GerstnerWave(double phase, double amplitude,
                Dvector direction, double frequence);
        GerstnerWave(GerstnerWave const& copie);
        ~GerstnerWave();
        GerstnerWave& operator=(const GerstnerWave 
                &copie);

};

