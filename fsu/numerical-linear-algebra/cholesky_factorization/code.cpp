/*
 * Daniel Gonzalez
 * dgonzale@math.fsu.edu
 * Florida State University Dept. of Mathematics
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <math.h>
#include "la.h"
using namespace std;

vector<vector<double>> cholesky(vector<vector<double>> A){
    int n = A.size();
    vector<vector<double>> L(n, vector<double>(n));

    for(int j = 0; j < n; j++){
        double sum = 0;
        for(int k = 0; k < j; k++)
            sum += L[j][k]*L[j][k];
        L[j][j] = sqrt(A[j][j] - sum);
        for(int i = j+1; i < n; i++){
            sum = 0;
            for(int k = 0; k < j; k++)
                sum += L[i][k]*L[j][k];
            L[i][j] = (A[i][j] - sum)/L[j][j];
        }
    }

    return L;
}

//SYMMETRIC TOEPLITZ MATRIX IS GIVEN BY THE VECTOR OF ITS FIRST ROW
vector<vector<double>> schur(vector<double> A){
    int n = A.size();
    vector<vector<double>> L;
    vector<vector<double>> G(2, vector<double>(n));
    double a = sqrt(A[0]);
    for(int i = n-1; i >= 0; i--)
        A[i] = A[i]/a;
    G[0] = A;
    G[1] = A;
    G[1][0] = 0;
    for(int k = 0; k < n-1; k++){
        L.push_back(G[0]);
        for(int i = n-1; i > k; i--)
            G[0][i] = G[0][i-1];
        G[0][k] = 0;
        double x = G[1][k+1]/G[0][k+1];
        double c = 1/sqrt(1 - pow(x, 2));
        double s = c*x;
        vector<vector<double>> U = {{c, -s}, {-s, c}};
        G = product(U, G);
    }
    L.push_back(G[0]);
    return transpose(L);
}

string test_cholesky(int trials){
    srand(time(NULL));
    int ctr = 0;
    for(int i = 0; i < trials; i++){
        int n = rand()%10 + 2;
        int mod = rand()%10 + 4;
        vector<vector<double>> A = generate_spd_matrix(n, mod);
        vector<vector<double>> L = cholesky(A);
        ctr = equality(A, product(L, transpose(L))) ? (ctr+1) : ctr;
    }
    return to_string(ctr) + " out of " + to_string(trials) + " correct.";
}

string test_schur(int trials){
    srand(time(NULL));
    int ctr = 0;
    for(int i = 0; i < trials; i++){
        int n = rand()%10 + 2;
        int mod = rand()%10 + 4;
        vector<double> A = generate_spd_toeplitz(5, 10);
        vector<vector<double>> L = schur(A);
        ctr = equality(full_toeplitz(A), product(L, transpose(L))) ? (ctr+1) : ctr;
    }
    return to_string(ctr) + " out of " + to_string(trials) + " correct.";
}

int main(int argc, char *argv[]){
    cout << "Cholesky Test:" << endl << test_cholesky(10000) << endl << endl;
    cout << "Schur Test:" << endl << test_schur(10000) << endl;
}
