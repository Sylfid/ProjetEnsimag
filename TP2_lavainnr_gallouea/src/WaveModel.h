#include <string>
#include "Height.h"


class WaveModel{
    private:
        Height* wave;
        Dvector* wind;
        Dvector* alignment;
        double intensite;
        double waveLength;
    public:
        WaveModel();
        WaveModel(Height* wave, Dvector* wind, Dvector* alignment, double intensite,
                double waveLenght) ;
        ~WaveModel()=0;
        void display(std::ostream& str) const;

}
