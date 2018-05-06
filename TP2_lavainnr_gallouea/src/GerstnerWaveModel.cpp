#include <exception>
#include <string>
#include <iostream>
#include "GerstnerWaveModel.h"
#include <cstdlib>

GerstnerWaveModel::GerstnerWaveModel() : WaveModel(){
    gerstnerWave=NULL;
    taille=0;
}

GerstnerWaveModel::GerstnerWaveModel(Dvector wind, Dvector 
        alignment, double intensite, double waveLength, double 
        param, double phase, double amplitude, double frequence,
        int taille):
    WaveModel(wind,alignment,intensite,waveLength,param){
        gerstnerWave = (GerstnerWave**)malloc(taille*
                taille*sizeof(GerstnerWave*));
        this->taille=taille*taille;
        for(int i=0;i<taille;i++){
            for(int j=0;j<taille;j++){
                gerstnerWave[i*taille+j]= new 
                    GerstnerWave(phase,amplitude,wind,
                    frequence,(double)i,(double)j);
            }
        }
    }
    

GerstnerWaveModel::GerstnerWaveModel(GerstnerWaveModel const& copie):
    WaveModel(copie){
        taille=copie.taille;
        gerstnerWave=(GerstnerWave**)malloc(copie.taille
                * sizeof(GerstnerWave*));
       for(int i=0; i<taille; i++){
          gerstnerWave[i] = new GerstnerWave(*copie.gerstnerWave[i]);
       }
    }

GerstnerWaveModel::~GerstnerWaveModel(){
    std::cout << "Destructeur GerstnerWaveModel\n";
    for(int i=0;i<taille;i++){
        delete gerstnerWave[i];
    }
    free(gerstnerWave);
}

GerstnerWaveModel& GerstnerWaveModel::operator=(GerstnerWaveModel 
        const& copie){
    for(int i=0;i<taille;i++){
        delete gerstnerWave[i];
    }
    taille=copie.taille;
    free(gerstnerWave);
    gerstnerWave = (GerstnerWave**)malloc(taille*sizeof(GerstnerWave*));
    for(int i=0;i<taille;i++){
        gerstnerWave[i] = new GerstnerWave(*copie.gerstnerWave[i]);
    }
    return *this;
}

double GerstnerWaveModel::operator()(int x, int y, int t) const{
    Dvector position;
    double hauteur(0);
    for(int i=0; i<taille; i++){
        position=(*gerstnerWave[i])((double) t);
        if((int) position(0)== x && (int) position(1)==y){
            hauteur+=position(2);
        }
        position.~Dvector();
    }
    return hauteur;
}
