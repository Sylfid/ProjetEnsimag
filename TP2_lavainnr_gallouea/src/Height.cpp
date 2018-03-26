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
    std::cout << "Destructeur\n";
    free(lignex);
}

void Height::display(std::ostream& str) const{
    int i=0;
    for(i=0;i<tailley;i++){
        this->lignex[i]->display(str);
    }
}

