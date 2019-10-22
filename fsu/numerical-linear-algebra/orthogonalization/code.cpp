/*
 * Daniel Gonzalez
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

vector<vector<precision>> identity(int n){
    vector<vector<precision>> I(n, vector<precision>(n));
    for(int i = 0; i < n; i++)
        I[i][i] = 1;
    return I;
}

vector<vector<precision>> random_matrix(int n){
    srand(time(NULL));
    vector<vector<precision>> A(n, vector<precision>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            A[i][j] = rand() % n;
    return A;
}

vector<vector<precision>> householder(vector<vector<precision>> A){
    int n = A.size();
    vector<vector<precision>> Q(n, vector<precision>(n));
    for(int i = 0; i < n; i++)
        Q[i][i] = 1;
    for(int i = 0; i < n - 1; i++){
        vector<precision> x(n);
        precision v = A[i][i];
        precision norm = 0;
        for(int j = i; j < n; j++)
            norm += A[j][i]*A[j][i];
        norm = sqrt(norm);
        x[i] = v - norm;
        for(int j = i + 1; j < n; j++)
            x[j] = A[j][i];
        A[i][i] = -norm;
        norm = 2*norm*(norm - v);
        x = scale(1/sqrt(norm), x);
        Q = difference(Q, outer_product(scale(2, x), product({x}, Q)[0]));
        for(int j = i + 1; j < n; j++){
            precision u = (v - A[i][i])*A[i][j];
            for(int l = i + 1; l < n; l++)
                u += A[l][i]*A[l][j];
            A[i][j] -= 2*u*(v - A[i][i])/norm;
            for(int l = i + 1; l < n; l++)
                A[l][j] -= 2*u*A[l][i]/norm;
        }
        for(int j = i + 1; j < n; j++)
            A[j][i] = 0;
    }
    return transpose(Q);
}

vector<vector<precision>> classical_gram_schmidt(vector<vector<precision>> A){
    int n = A.size();
    vector<precision> u(n);
    for(int i = 0; i < n; i++){
        u = A[i];
        for(int j = 0; j < i; j++)
            A[i] = difference(A[i], scale(inner_product(A[j], u), A[j]));
        A[i] = scale(1/norm_L2(A[i]), A[i]);
    }
    return A;
}

vector<vector<precision>> modified_gram_schmidt(vector<vector<precision>> A){
    int n = A.size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++)
            A[i] = difference(A[i], scale(inner_product(A[j], A[i]), A[j]));
        A[i] = scale(1/norm_L2(A[i]), A[i]);
    }
    return A;
}

int main(int argc, char* argv[]){
    int n = 5;
    vector<vector<precision>> I = identity(n);
    vector<vector<precision>> A = random_matrix(n);
    vector<vector<precision>> Q = householder(A);
    vector<vector<precision>> CGS = classical_gram_schmidt(A);
    vector<vector<precision>> MGS = modified_gram_schmidt(A);

    vector<vector<precision>> error_Q = difference(product(transpose(Q), Q), I);
    vector<vector<precision>> error_CGS = difference(product(transpose(CGS), CGS), I);
    vector<vector<precision>> error_MGS = difference(product(transpose(MGS), MGS), I);

    cout << "Householder Reflector Max Error:\t" << norm_inf(error_Q) << endl;
    cout << "Classical Gram-Schmidt Max Error:\t" << norm_inf(error_CGS) << endl;
    cout << "Modified Gram-Schmidt Max Error:\t" << norm_inf(error_MGS) << endl;

    return 0;
}
