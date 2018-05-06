#ifndef OCEAN_H
#define OCEAN_H

#include "WaveModel.h"
#include "Height.h"

class Ocean{
    private:
        int nx;
        int ny;
        double lx;
        double ly;
        int t;
        Height* h;
        WaveModel* model;
    public:
        Ocean(double lenx, double leny, int numx, int numy);
        void computeHeight();
        void increaseTime();
        ~Ocean();
        void display();
};
#endif
