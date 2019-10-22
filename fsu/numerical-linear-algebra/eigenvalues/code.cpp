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
#include "test_cases.h"

//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

const precision π = M_PI;

//A = A + α(xyᵀ + (y + αβx)xᵀ)
//RETURNS THE TRIDIAGONAL FORM OF A SYMMETRIC POSITIVE-DEFINITE MATRIX
vector<vector<precision>> householder(vector<vector<precision>> A){
    int n = A.size();
    vector<vector<precision>> T(2);
    for(int k = 0; k < n - 2; k++){
        precision α;
        precision β;
        precision γ;
        precision δ;
        vector<precision> x;
        vector<precision> y;
        vector<precision> z;
        vector<vector<precision>> xyT(n - k - 1);
        vector<vector<precision>> zxT(n - k - 1);
        for(int i = k+1; i < n; i++)
            x.push_back(A[i][k]);
        γ = ((A[k + 1][k] < 0) ? -1 : 1)*norm_L2(x);
        δ = x[0]*γ + pow(γ, 2);
        x[0] = x[0] + γ;
        α = -1/δ;
        y = product(A, x);
        β = inner_product(x, y);
        z = sum(y, scale(α*β, x));
        A = sum(A, scale(α, sum(outer_product(x, y), outer_product(z, x))));
        A[k + 1][k] = -γ;
    }
    for(int i = 0; i < A.size(); i++)
        T[0].push_back(A[i][i]);
    for(int i = 0; i < A.size()-1; i++)
        T[1].push_back(A[i + 1][i]);
    return T;
}

//FINDS THE EIGENVALUES OF A SYMMETRIC TRIDIAGONAL MATRIX UP TO SOME ERROR THRESHOLD
vector<precision> eigenvalues(vector<vector<precision>> T, precision threshold){
    int n = T[0].size();
    vector<precision> Λ;
    for(int l = 1; l < n; l++){
        while(abs(T[1][n - l - 1]) > threshold){
            precision a = T[0][0];
            precision b = T[1][0];
            precision c = T[0][1];
            precision d;
            precision e = T[1][1];
            precision ρ = sqrt(pow(a, 2) + pow(b, 2));
            precision γ = a/ρ;
            precision σ = -b/ρ;
            T[0][0] = γ*γ*a - 2*σ*γ*b + σ*σ*c;
            T[1][0] = σ*γ*a + γ*γ*b - σ*σ*b - σ*γ*c;
            T[0][1] = σ*σ*a + 2*σ*γ*b + γ*γ*c;
            T[1][1] = γ*e;
            precision bulge = -σ*e;
            for(int k = 1; k < n - l; k++){
                ρ = sqrt(pow(T[1][k - 1], 2) + pow(bulge, 2));
                γ = T[1][k - 1]/ρ;
                σ = -bulge/ρ;
                a = T[0][k];
                b = T[1][k];
                c = T[0][k + 1];
                d = T[1][k - 1];
                e = T[1][k + 1];
                T[1][k - 1] = γ*d - σ*bulge;
                T[0][k] = γ*γ*a - 2*σ*γ*b + σ*σ*c;
                T[1][k] = σ*γ*a + γ*γ*b - σ*σ*b - σ*γ*c;
                T[0][k + 1] = σ*σ*a + 2*σ*γ*b + γ*γ*c;
                if(k < n - 2){
                    T[1][k + 1] = γ*e;
                    bulge = -σ*e;
                }
            }
        }
        Λ.push_back(T[0][T[0].size() - l]);
    }
    Λ.push_back(T[0][0]);
    return Λ;
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    int n = 6;
    precision threshold = pow(10, -5);

    cout << "Random Eigenvalues with Random Orthonormal Basis:" << endl;
    vector<vector<precision>> Λ = eigenmatrix(n);
    vector<vector<precision>> Q = gram_schmidt(n);
    vector<vector<precision>> A = product(product(Q, Λ), transpose(Q));
    for(int i = 0; i < n - 1; i++)
        A[i].erase(A[i].begin() + i + 1, A[i].begin() + n);
    cout << "Λ = " << endl;
    print_matrix(Λ);
    cout << "A = QΛQᵀ = " << endl;
    print_matrix(A);
    cout << "Computed eigenvalues of A:" << endl;
    print_vector(eigenvalues(householder(A), threshold));

    cout << "---------------------------------------------" << endl << endl;

    cout << "Random symmetric tridiagonal Toeplitz matrix:" << endl;
    //vector<vector<precision>> T = generate_toeplitz_tri(n);
    vector<vector<precision>> T =
    {
        {6, 6, 6, 6, 6, 6},
        {7, 7, 7, 7, 7}
    };
    print_matrix(T);

    cout << "Eigenvalues from formula:" << endl;
    for(int k = n; k > 0; k--)
        cout << "λ" << k << ": " << T[0][0] + 2*T[1][0]*cos(k*π/(n + 1)) << endl;
    cout << endl;

    cout << "Eigenvalues computed:" << endl;
    vector<precision> ΛT = eigenvalues(T, threshold);
    sort(ΛT.begin(), ΛT.end());
    print_vector(ΛT);

    return 0;
}
