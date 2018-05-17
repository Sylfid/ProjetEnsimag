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
        Ocean(double lenx, double leny, int numx, int numy, WaveModel* mod);
        Ocean(Ocean const& copie);
        Ocean& operator=(Ocean const& copie);
        void computeHeight();
        void increaseTime();
        ~Ocean();
        void display();
        void init_gl_VertexArrayY(const int x, double* const vertices) const;
        void gl_VertexArrayX(const int y, double* const vertices) const;
        void gl_VertexArrayY(const int x, double* const vertices) const;
};
#endif
