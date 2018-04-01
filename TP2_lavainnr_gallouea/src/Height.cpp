#include <exception>
#include <string>
#include <iostream>
#include "Height.h"
#include <cstdlib>


Height::Height(){
   lignex = (Dvector**) malloc(2*sizeof(Dvector*));
   this->tailley=2;
   int i(0);
   for(i=0;i<tailley;i++){
       lignex[i]= new Dvector();
   }
}

Height::Height(int taillex, int tailley){
   this->lignex = (Dvector**) malloc(tailley*sizeof(Dvector*));
   this->tailley=tailley;
   int i(0);
   for(i=0;i<tailley;i++){
       this->lignex[i]= new Dvector(taillex);
   }
}


Height::~Height(){
    std::cout << "Destructeur Height\n";
    int i(0);
    for(i=0;i<this->tailley;i++){
        std::cout<<i;
        delete lignex[i];
    }
    free(lignex);
}

void Height::display(std::ostream& str) const{
    int i=0;
    for(i=0;i<tailley;i++){
        this->lignex[i]->display(str);
    }
}

double & Height::operator()(int i, int j) const{
    try{
        if(j<0 || j>this->tailley || i<0 
                || i>1){//this->lignex[j].taille-1){
            throw std::string("Dépassement de taille pour Dvector");
        }
        else{
            return this->lignex[i].getComposante(j);
        }
    }catch(std::string const& chaine){
        std::cerr << chaine << std::endl;
        throw std::string("Dépassement de taille pour Dvector");
    }
}

