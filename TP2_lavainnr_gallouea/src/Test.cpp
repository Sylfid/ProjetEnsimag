#include <assert.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Height.h"

using namespace std;

int main(){
    Height test(4,4);
    Height test2(4,4);
    for (int i = 0; i < 4; i ++){
        for (int j = 0; j < 4; j ++){
            test(i, j) = 4*i + j;
        }
    }
    cout<<"4*2 + 3 = "<<test(2,3)<<endl;
    test.display(cout);
    test2=test;
    cout<<"yoyoyyo";
    //cout << "\n\n salut \n\n";
    //test2.display(cout);
    return 0;
}
