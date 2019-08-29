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

const precision π = M_PI;

//A = A + α(x ⊗ y + (y + αβx) ⊗ x)
vector<vector<precision>> householder(vector<vector<precision>> A)
{
	int n = A.size();
	for(int k = 0; k < n - 2; k++)
	{
		precision α;
		precision β;
		precision γ;
		precision δ;
		vector<precision> x;
		vector<precision> y;
		vector<precision> z;
		vector<vector<precision>> xyT(n-k-1);
		vector<vector<precision>> zxT(n-k-1);
		for(int i = k+1; i < n; i++)
			x.push_back(A[i][k]);
		γ = ((A[k+1][k] < 0) ? -1 : 1)*norm_L2(x);
		δ = x[0]*γ + pow(γ, 2);
		x[0] = x[0] + γ;
		α = -1/δ;
		y = product(A, x);
		β = inner_product(x, y);
		z = sum(y, scale(α*β, x));
		A = sum(A, scale(α, sum(outer_product(x, y), outer_product(z, x))));
		A[k+1][k] = -γ;
	}
	return A;
}

//⌜x d +  ⌝
//|d a b  |
//|+ b c e|
//⌞    e x⌟
vector<precision> eigenvalues(vector<vector<precision>> T, precision threshold)
{
	int n = T[0].size();
	vector<precision> Λ;
	for(int l = 1; l < n; l++)
	{
		while(abs(T[1][T[1].size()-l]) > threshold)
		{
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
			for(int k = 1; k < n-l; k++)
			{
				ρ = sqrt(pow(T[1][k-1], 2) + pow(bulge, 2));
				γ = T[1][k-1]/ρ;
				σ = -bulge/ρ;
				a = T[0][k];
				b = T[1][k];
				c = T[0][k+1];
				d = T[1][k-1];
				e = T[1][k+1];
				T[1][k-1] = γ*d - σ*bulge;
				T[0][k] = γ*γ*a - 2*σ*γ*b + σ*σ*c;
				T[1][k] = σ*γ*a + γ*γ*b - σ*σ*b - σ*γ*c;
				T[0][k+1] = σ*σ*a + 2*σ*γ*b + γ*γ*c;
				if(k < n-2)
				{
					T[1][k+1] = γ*e;
					bulge = -σ*e;
				}
			}
		}
		Λ.push_back(T[0][T[0].size()-l]);
	}
	Λ.push_back(T[0][0]);
	return Λ;
}

vector<precision> EVP(vector<vector<precision>> A, precision threshold)
{
	vector<vector<precision>> T(2);
	A = householder(A);
	for(int i = 0; i < A.size(); i++)
		T[0].push_back(A[i][i]);
	for(int i = 0; i < A.size()-1; i++)
		T[1].push_back(A[i+1][i]);
	return eigenvalues(T, threshold);
}

vector<vector<precision>> eigenvectors(vector<vector<precision>> A, vector<vector<precision>> G)
{
	int n = A.size();
	vector<vector<precision>> U;
	vector<vector<precision>> H(n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			H[i].push_back((j == i) ? 1 : 0);
	for(int k = 0; k < n-2; k++)
	{
		vector<precision> x;
		for(int i = 0; i <= k; i++)
			x.push_back(0);
		for(int i = k+2; i < n; i++)
			x.push_back(A[i][k]);
		x[k+1] = pow(A[k+1][k], 2);
		for(int i = k+2; i < n; i++)
			x[k+1] = x[k+1] - A[i][k];
		x[k+1] = x[k+1] + norm_L2(x);
		//incomplete due to time constraints
		//please read the report for an explanation
	}
	return U;
}


int main(int argc, char* argv[])
{
	int n = 6;
	vector<vector<precision>> A(n);

	A[0].push_back(4);
	A[1].push_back(1);
	A[1].push_back(2);
	A[2].push_back(2);
	A[2].push_back(0);
	A[2].push_back(3);
	A[3].push_back(-5);
	A[3].push_back(4);
	A[3].push_back(-1);
	A[3].push_back(1);
	A[4].push_back(1);
	A[4].push_back(5);
	A[4].push_back(2);
	A[4].push_back(5);
	A[4].push_back(-2);
	A[5].push_back(4);
	A[5].push_back(3);
	A[5].push_back(1);
	A[5].push_back(2);
	A[5].push_back(4);
	A[5].push_back(1);

	vector<precision> Λ = EVP(A, pow(10, -5));

	for(int i = 0; i < n; i++)
		cout << Λ[i] << endl;

	return 0;
}
