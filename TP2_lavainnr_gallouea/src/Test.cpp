#include "Dvector.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

int main(){
  Dvector v(3,2.5);
  assert( v.size()==3);
  v.display(cout);
  std::stringstream str;
  v.display(str);
  assert(str.str()=="2.5\n2.5\n2.5\n");
  std::cout << "display fonctionne\n" ;
  Dvector vect("fichierTest");
  vect.display(cout);
  return 0;
}
