#include <string>


class Dvector{
    private:
        double* composante;
        int taille;
    public:
        Dvector();
        Dvector(int taille2);
        Dvector(Dvector const& copie);
        Dvector(int taille2, double initialisation);
        Dvector(std::string file);
        ~Dvector();
        void display(std::ostream& str);
        void setVector(int i, double newvaleur);
        void addValeur(double newValeur);
        void fillRandomly();
        int size();
        double operator()(int i);
        Dvector& operator=(const Dvector &v);
        void operator+=(const Dvector &v);
        void operator+=(int i);
        void operator-=(const Dvector &v);
        void operator-=(int i);
};

