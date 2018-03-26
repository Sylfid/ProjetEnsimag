#include <assert.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Height.h"

using namespace std;

int main(){
    Height* test(new Height(4,4));
    //test->display(cout);
    free(test);
    return 0;
}
