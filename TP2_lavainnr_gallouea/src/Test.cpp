#include "fft.cpp"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Ocean.h"
#include "GerstnerWaveModel.h"

using namespace std;

int main(){
    /*Height test(4,4);
    for (int i = 0; i < 4; i ++){
        for (int j = 0; j < 4; j ++){
            test(i, j) = 4*i + j;
        }
    }
    cout<<"4*2 + 3 = "<<test(2,3)<<endl;
    test.display(cout);
    Height test2(test);
    cout<<"yoyoyyo";
    cout << "\n\n salut \n\n";
    test2.display(cout);
    Dvector vent(2,1);
    Dvector alignement(2,0.5);
    GerstnerWaveModel model(vent, alignement, 5, 10, 0, 30, 30);
    Ocean ocean(640, 480, 30, 30, &model);
    ocean.increaseTime();
    ocean.computeHeight();
    ocean.display();
    return 0;
    */
    vector<comp> x;
    x.resize(8);
    for (int k(0); k < 8; k++){
        x[k] = comp(k* 0.1, 0);
        cout << x[k] << endl;
    }
    fft(x);
    for (int k(0); k < 8; k++){
        cout << x[k] << endl;
    }
}
