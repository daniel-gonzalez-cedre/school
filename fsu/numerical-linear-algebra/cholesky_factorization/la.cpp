/*
 * Daniel Gonzalez
 * dgonzale@math.fsu.edu
 * Florida State University Dept. of Mathematics
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
using namespace std;

void print_vector(vector<double> x){
    for(int i = 0; i < x.size(); i++)
        cout << x[i] << " ";
    cout << endl;
}

void print_matrix(vector<vector<double>> A){
    for(int i = 0; i < A.size(); i++){
        for(int j = 0; j < A[0].size(); j++)
            cout << A[i][j] << "\t";
        cout << endl;
    }
}

vector<double> generate_spd_toeplitz(int n, int mod){
    srand(time(NULL));
    vector<vector<double>> T(n, vector<double>(n));
    vector<double> u(n);
    double sum = 0;
    for(int i = 1; i < n; i++){
        u[i] = rand()%mod;
        sum += u[i];
    }
    u[0] = sum + 1;
    return u;
}

vector<vector<double>> full_toeplitz(vector<double> A){
    int n = A.size();
    vector<vector<double>>T(n, vector<double>(n));
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++)
            T[i][j] = A[j-i];
        for(int j = 0; j < i; j++)
            T[i][j] = T[j][i];
    }
    return T;
}

vector<vector<double>> generate_spd_matrix(int n, int mod){
    srand(time(NULL));
    vector<vector<double>> R(n, vector<double>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++)
            R[i][j] = rand()%mod;
        for(int j = i-1; j >= 0; j--)
            R[j][i] = R[i][j];
    }
    for(int i = 0; i < n; i++){
        double sum = 0;
        for(int j = 0; j < n; j++)
            sum = (i != j) ? (sum + R[i][j]) : sum;
        R[i][i] = sum + 1;
    }
    return R;
}

vector<vector<double>> transpose(vector<vector<double>> A){
    vector<vector<double>> T(A[0].size(), vector<double>(A.size()));
    for(int i = 0; i < A.size(); i++)
        for(int j = 0; j < A[0].size(); j++)
            T[j][i] = A[i][j];
    return T;
}

vector<vector<double>> product(vector<vector<double>> A, vector<vector<double>> B){
    vector<vector<double>> C(A.size());
    for(int i = 0; i < A.size(); i++){
        for(int j = 0; j < B[0].size(); j++){
            double sum = 0;
            for(int k = 0; k < A[0].size(); k++)
                sum += A[i][k]*B[k][j];
            C[i].push_back(sum);
        }
    }
    return C;
}

bool equality(vector<vector<double>> A, vector<vector<double>> B){
    bool eq = false;
    if(A.size() != B.size() || A[0].size() != B[0].size())
        return eq;
    for(int i = 0; i < A.size(); i++)
        for(int j = 0; j < A[0].size(); j++)
            eq = eq || A[i][j] == B[i][j];
    return eq;
}
