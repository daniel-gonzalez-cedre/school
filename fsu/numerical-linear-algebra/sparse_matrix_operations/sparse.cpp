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

//COMPRESSED SPARSE ROW FORMAT
struct CSR{
    vector<double> data;
    vector<double> rows;
    vector<double> cols;
};

//COMPRESSED SPARSE COLUMN FORMAT
struct CSC{
    vector<double> data;
    vector<double> rows;
    vector<double> cols;
};

//COMPRESSED SPARSE DIAGONAL FORMAT
struct CSD{
    vector<vector<double>> diag;
    vector<double> ioff;
};

void print_vector(vector<double> x, string name){
    cout << name << ": [ ";
    for(int i = 0; i < x.size(); i++)
        cout << x[i] << " ";
    cout << "]" << endl;
}

void print_matrix(vector<vector<double>> A, string name){
    cout << name << ": " << endl;
    for(int i = 0; i < A.size(); i++){
        for(int j = 0; j < A[0].size(); j++)
            cout << A[i][j] << "\t";
        cout << endl;
    }
}

vector<double> generate_random_vector(int n){
    srand(time(NULL));
    vector<double> u(n);
    for(int i = 0; i < n; i++)
        u[i] = rand()%n;
    return u;
}
vector<vector<double>> generate_random_matrix(int n1, int n2){
    srand(time(NULL));
    vector<vector<double>> R(n1, vector<double>(n2));
    for(int i = 0; i < n1; i++)
        for(int j = 0; j < n2; j++)
            R[i][j] = rand()%n2;
    return R;
}

vector<vector<double>> transpose(vector<vector<double>> A){
    vector<vector<double>> T(A[0].size(), vector<double>(A.size()));
    for(int i = 0; i < A.size(); i++)
        for(int j = 0; j < A[0].size(); j++)
            T[j][i] = A[i][j];
    return T;
}

vector<vector<double>> dense_product(vector<vector<double>> A, vector<vector<double>> B){
    vector<vector<double>> C(A.size());
    for(int i = 0; i < A.size(); i++){
        for(int j = 0; j < B[0].size(); j++){
            int sum = 0;
            for(int k = 0; k < A[0].size(); k++)
                sum += A[i][k]*B[k][j];
            C[i].push_back(sum);
        }
    }
    return C;
}

//COMPRESSED ROW CONVERSION
CSR compress_CSR(vector<vector<double>> A){
    CSR sparse;
    for(int i=0, ptr=0; i < A.size(); i++){
        sparse.rows.push_back(ptr);
        for(int j=0; j < A[0].size(); j++){
            if(A[i][j] != 0){
                sparse.data.push_back(A[i][j]);
                sparse.cols.push_back(j);
                ptr++;
            }
        }
    }
    sparse.rows.push_back(sparse.data.size());
    return sparse;
}

//COMPRESSED COLUMN CONVERSION
CSC compress_CSC(vector<vector<double>> A){
    CSC sparse;
    for(int j=0, ptr=0; j < A[0].size(); j++){
        sparse.cols.push_back(ptr);
        for(int i=0; i < A.size(); i++){
            if(A[i][j] != 0){
                sparse.data.push_back(A[i][j]);
                sparse.rows.push_back(i);
                ptr++;
            }
        }
    }
    sparse.cols.push_back(sparse.data.size());
    return sparse;
}

//COMPRESSED DIAGONAL CONVERSION
CSD compress_CSD(vector<vector<double>> A){
    CSD sparse;
    int m = A.size();
    for(int d = m-1; d > 0; d--){
        bool flag = false;
        vector<double> curr;
        for(int i = 0; i < d; i++)
            curr.push_back(0);
        for(int i = d, j = 0; (i < m) && (j < m-d); i++, j++){
            flag = (A[i][j]!=0) ? true : (flag || false);
            curr.push_back(A[i][j]);
        }
        if(flag){
            sparse.diag.push_back(curr);
            sparse.ioff.push_back(-d);
        }
    }
    for(int d = 0; d < m; d++){
        bool flag = false;
        vector<double> curr;
        for(int i = 0, j = d; (i < m-d) && (j < m); i++, j++){
            flag = (A[i][j]!=0) ? true : (flag || false);
            curr.push_back(A[i][j]);
        }
        for(int i = 0; i < d; i++)
            curr.push_back(0);
        if(flag){
            sparse.diag.push_back(curr);
            sparse.ioff.push_back(d);
        }
    }
    sparse.diag = transpose(sparse.diag);
    return sparse;
}

//SPARSE ROW PRODUCT
vector<double> product_CSR(CSR sparse, vector<double> x){
    vector<double> y;
    for(int k = 0; k < x.size(); k++){
        double k1 = sparse.rows[k];
        double k2 = sparse.rows[k+1];
        y.push_back(0);
        for(int i = k1; i < k2; i++)
            y[y.size()-1] += sparse.data[i]*x[sparse.cols[i]];
    }
    return y;
}

//SPARSE COLUMN PRODUCT
vector<double> product_CSC(CSC sparse, vector<double> x){
    vector<double> y(x.size());
    for(int k = 0; k < x.size(); k++){
        double k1 = sparse.cols[k];
        double k2 = sparse.cols[k+1];
        for(int i = k1; i < k2; i++)
            y[sparse.rows[i]] += + x[k]*sparse.data[i];
    }
    return y;
}

//SPARSE DIAGONAL PRODUCT
vector<double> product_CSD(CSD sparse, vector<double> x){
    vector<double> y(x.size());
    for(int j = 0; j < sparse.ioff.size(); j++){
        int off = sparse.ioff[j];
        int low = (off >= 0) ? 0 : (1-off);
        int hi = (off >= 0) ? x.size()-off : x.size();
        for(int i = low; i < hi; i++)
            y[i] += sparse.diag[i][j]*x[off+i];
    }
    return y;
}

//DENSE MATRIX-MATRIX PRODUCT BY DIAGONALS
vector<vector<double>> diag_product(vector<vector<double>> A, vector<vector<double>> B){
    int n1 = A.size();
    int n2 = B.size();
    int n3 = B[0].size();
    vector<vector<double>> C(n1);
    for(int i = 0; i < n1; i++)
        for(int j = 0; j < n3; j++)
            C[i].push_back(0);

    for(int i = 1-n1; i < n2; i++){
        for(int j = 1-n2; j < n3; j++){
            int αi = (i < 0) ? (-i) : 0;
            int βi = (j < 0) ? (-j) : 0;
            int αj = αi + i;
            int βj = βi + j;

            if(αj < βi){
                αj = βi;
                αi = αj-i;
            } else if(αj > βi){
                βi = αj;
                βj = βi+j;
            }

            while(αi < min(n1, n2-i) && βi < min(n2, n3-j)){
                C[αi][βj] += A[αi][αj]*B[βi][βj];
                αi++, αj++, βi++, βj++;
            }
        }
    }

    return C;
}

//SOME TEST CASES
int main(int argc, char *argv[]){
    vector<vector<double>> A =
    {
        {1, 0, 0, 2, 0},
        {3, 4, 0, 5, 0},
        {6, 0, 7, 8, 9},
        {0, 0, 10, 11, 0},
        {0, 0, 0, 0, 12}
    };
    vector<vector<double>> B =
    {
        {1, 0, 2, 0, 0},
        {3, 4, 0, 5, 0},
        {0, 6, 7, 0, 8},
        {0, 0, 9, 10, 0},
        {0, 0, 0, 11, 12}
    };
    vector<vector<double>> C =
    {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
    };
    vector<vector<double>> D =
    {
        {3, 2, 1},
        {3, 2, 1},
        {3, 2, 1},
        {3, 2, 1},
        {3, 2, 1}
    };
    vector<double> x1 = {0, 3, -2, 1, -1};
    // Ax = {2, 17, -15, -9, -12}
    // Bx = {-4, 17, -4, -8, 1}

    print_matrix(A, "A");
    cout << endl;
    print_matrix(B, "B");
    cout << endl;
    print_matrix(C, "C");
    cout << endl;
    print_matrix(D, "D");
    cout << endl;

    print_vector(x1, "x1");
    cout << endl;

    print_vector(product_CSR(compress_CSR(A), x1), "Ax1 CSR");
    print_vector(product_CSC(compress_CSC(A), x1), "Ax1 CSC");
    print_vector(product_CSD(compress_CSD(A), x1), "Ax1 CSD");
    print_vector(product_CSD(compress_CSD(B), x1), "Bx1 CSD");
    print_matrix(diag_product(A, B), "AB");
    print_matrix(diag_product(C, D), "CD");

    print_matrix(generate_random_matrix(5, 5), "random");
}
