#include <string>
#include "Height.h"


class WaveModel{
    private:
        Height* wave;
        Dvector* wind;
        Dvector* alignment;
        double intensite;
        double waveLength;
        double param;
    public:
        WaveModel();
        WaveModel(Height wave, Dvector wind, Dvector alignment, 
                double intensite, double waveLenght, double param) ;
        WaveModel(WaveModel const& copie);
        ~WaveModel();
        WaveModel& operator=(const WaveModel &w);
        void display(std::ostream& str) const;

};
