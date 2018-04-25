#include <assert.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "WaveModel.h"

using namespace std;

int main(){
    /*Height test(4,4);
    Height test2(5,5);
    for (int i = 0; i < 4; i ++){
        for (int j = 0; j < 4; j ++){
            test(i, j) = 4*i + j;
        }
    }
    cout<<"4*2 + 3 = "<<test(2,3)<<endl;
    test.display(cout);
    test2=test;
    cout<<"yoyoyyo";
    cout << "\n\n salut \n\n";
    test2.display(cout);*/
    Height test(4,4);
    Dvector vent(2,2);
    Dvector alignement(2,2);
    WaveModel ouii(test,vent,alignement, 4.0, 4.0, 4.0);
    return 0;
}
