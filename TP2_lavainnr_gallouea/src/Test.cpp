#include <assert.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Ocean.h"

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
    Height test(4,4);
    Dvector vent(2,1);
    Dvector alignement(2,0.5);
    GerstnerWaveModel model(vent, alignement, 5, 10, 0, 2, 2);
    cout << model(1, 0, 5) << endl;*/
    Ocean ocean(640, 480, 30, 30);
    ocean.increaseTime();
    ocean.computeHeight();
    ocean.display();
    return 0;
}
