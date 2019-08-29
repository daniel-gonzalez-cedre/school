/*
 * Daniel Gonzalez
 * dgonzale@math.fsu.edu
 * Florida State University Dept. of Mathematics
 */
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <math.h>
#include <time.h>
#include <cmath>
#include <complex>
using namespace std;

#include "linear_algebra.h"
#include "norms.h"

//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

vector<vector<precision>> generate_toeplitz_tri(int dim){
    srand(time(NULL));
    precision a = (rand() % dim) + 1;
    precision b = (rand() % dim) + 1;
    vector<vector<precision>> T(2);
    for(int i = 0; i < dim; i++)
        T[0].push_back(a);
    for(int i = 0; i < dim - 1; i++)
        T[1].push_back(b);
    return T;
}

vector<vector<precision>> gram_schmidt(int n){
    srand(time(NULL));
    vector<precision> v(n);
    vector<precision> u(n);
    vector<vector<precision>> Q;
    for(int i = 0; i < n; i++){
        for(int i = 0; i < n; i++)
            v[i] = rand() % n;
        u = v;
        for(int j = 0; j < i; j++)
            u = difference(u, scale(inner_product(Q[j], u)/inner_product(Q[j], Q[j]), Q[j]));
        u = scale(1/norm_L2(u), u);
        bool zero = false;
        for(int i = 0; i < n; i++)
            zero = (u[i] == 0) || zero;
        if(zero)
            i--;
        else
            Q.push_back(u);
    }
    return Q;
}

vector<vector<precision>> eigenmatrix(int n){
    srand(time(NULL));
    vector<vector<precision>> Λ(n, vector<precision>(n));
    for(int i = 0; i < n; i++)
        Λ[i][i] = (rand() % n) + 1;
    return Λ;
}
