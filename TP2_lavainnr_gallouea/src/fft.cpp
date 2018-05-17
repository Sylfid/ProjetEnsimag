#include <vector>
#include <math.h>
#include <complex>
#include <iostream>

using namespace std;
typedef complex<double> comp; 

void fft(vector<comp> &x){
    int n(x.size());
    if (x.size() <= 1){
        return;
    }
    vector<comp> even, odd;
    even.resize(n/2);
    odd.resize(n/2);
    for(int k(0); k < n/2; k++){
        even[k] = x[2*k];
        odd[k] = x[2*k + 1];
    }
    fft(even);
    fft(odd);
    for(int k(0); k < n/2; k++){
        comp iarg(0.0, -2.0 * M_PI * k / n);  
        comp t = odd[k] * exp(iarg);
        x[k] = even[k] + t;
        x[k + n/2] = even[k] - t;
    }
}

void ifft(vector<comp> &x){
    int n(x.size());
    if (n <= 1){
        return;
    }
    for (int k(0); k < n; k++){
        x[k] = conj(x[k]);
    }
    fft(x);
    comp a(n, 0);
    for (int k(0); k < n; k++){
        x[k] = conj(x[k]) / a;
    }
}



