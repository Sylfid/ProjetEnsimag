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
        void display(std::ostream& str) const;
        void setVector(int i, double newvaleur);
        void addValeur(double newValeur);
        void fillRandomly();
        int size() const;
        double & operator()(int i) const;
        Dvector& operator=(const Dvector &v);
        void operator+=(const Dvector &v);
        void operator+=(int i);
        void operator-=(const Dvector &v);
        void operator-=(int i);
        void operator*=(double d);
        void operator/=(double d);
        void resize(int newTaille, double valeur);
        int getTaille();
        double getComposante(int i);
};

Dvector operator+(const Dvector &a, const Dvector &b);
Dvector operator-(const Dvector &a, const Dvector &b);
Dvector operator*(const Dvector &a, double b);
Dvector operator*(double b, const Dvector &a);
Dvector operator/(const Dvector &a, double b);
Dvector operator/(double b, const Dvector &a);
Dvector operator-(const Dvector &a);
bool operator==(const Dvector &a, const Dvector &b);
std::ostream& operator<<(std::ostream &str, const Dvector v);
std::istream& operator>>(std::istream &str, Dvector &v);
