#include <exception>
#include <string>
#include <iostream>
#include "Dvector.h"
#include <cstdlib>
#include <fstream>

Dvector::Dvector(){
    std::cout << "Constructeur sans argument\n";
    composante = new double[2];
    taille=2;
}

Dvector::Dvector(int taille2){
    std::cout << "Constructeur avec un int en argument\n";
    taille=taille2;
    if(!(taille>-1)) return ;
    if(taille==0){
        composante=NULL;
    }
    else{
        composante = new double[taille];
        int i(0);
        for(i=0;i<taille;i++){
            composante[i]=0;
        }
    }
}

Dvector::Dvector(int taille2, double initialisation){
    std::cout << "Constructeur avec un int et un double en argument\n";
    taille=taille2;
    if(!(taille>0)) return ;
    composante = (double*) malloc(taille*sizeof(double));
    int i=0;
    for(i=0;i<taille;i++){
        composante[i]=initialisation;
    }
}

Dvector::Dvector(Dvector const& copie){
    std::cout << "Constructeur par copie";
    taille=copie.taille;
    composante = new double[taille];
    int i(0);
    for(i=0;i<taille;i++){
        composante[i]=copie.composante[i];
    }
}

Dvector::Dvector(std::string file){
    std::cout << "Constructeur avec fichier\n";
    std::ifstream fluxVector(file.c_str());
    if(fluxVector){
        char a;
        composante = NULL;
        int b(0);
        int compteur(0);
        double* newComposante(NULL);
        int i(0);
        int flag(0);
        while(fluxVector.get(a)){
            if(a>47 && a<58){
                b=10*b+(a-48);
                flag=1;
            }
            else{
                if(flag==1){
                    compteur++;
                    newComposante=composante;
                    composante = (double*)malloc(compteur*sizeof(double));
                    for(i=0;i<compteur-1;i++){
                        composante[i]=newComposante[i];
                    }
                    composante[compteur-1]=b;
                    free(newComposante);
                    b=0;
                }
            }
        }
        taille=compteur;
    }
    else{
        taille=0;
        composante=NULL;
    }
}

Dvector::~Dvector(){
    std::cout << "Destructeur\n";
    free(composante);
}

void Dvector::display(std::ostream& str){
    int i=0;
    for(i=0;i<taille;i++){
        str << composante[i];
        str << "\n";
    }
}
void Dvector::setVector(int i, double newvaleur){
    if(!(i<taille)) return ;
    else{
        composante[i]=newvaleur;
    }
}

int Dvector::size(){
    return taille;
}


void Dvector::fillRandomly(){
    int i(0);
    double c;
    for(i=0;i<taille;i++){
        c=(double) (rand()%100000);
        c=c/100000;
        composante[i]=c;
    }
}

double Dvector::operator[](int i){
    try{
        if(i<0 || i>taille-1){
            throw std::string("Dépassement de taille pour Dvector");
        }
        else{
            
        }
    }catch(std::string const& chaine){
        std::cerr << chaine << std::endl;
    }
}
