#ifndef HEIGHT_H
#define HEIGHT_H


#include <string>
#include "Dvector.h"


class Height{
    private:
        Dvector** lignex;
        int tailley;
    public:
        Height();
        Height(int taillex, int tailley);
        Height(Height const& copie);
        ~Height();
        void display(std::ostream& str) const;
        double operator()(int i, int j) const;
        double & operator()(int i, int j);
        int getTailley() const;
        int getTaillex(int i) const;
        Height& operator=(const Height &h);
        //Dvector(Dvector const& copie);
        //Dvector(int taille2, double initialisation);
};

#endif
