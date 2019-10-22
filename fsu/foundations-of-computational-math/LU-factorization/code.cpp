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

#include "matrix.h"

//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

const precision PI = M_PI;

/* finds the in-place LU-factorization of a given matrix using various pivoting strategies
 * throws an exception if the divisor used to compute a Gauss transform is either 0 or has magnitude below a certain threshold
 *
 * A = an n by n matrix
 * partial = an integer flag indicating whether to do partial pivoting or not
 * complete = an integer flag indicating whether to do complete pivoting or not
 */
vector<vector<precision>> factor(vector<vector<precision>> A, int partial, int complete)
{
	int n = A.size();
	vector<precision> P;
	vector<precision> Q;
	for(int k = 0; k < n-1; k++)
	{
		if(partial)
		{//execute partial pivoting
			int max = k;
			for(int i = k+1; i < n; i++)
				if(abs(A[i][k]) > abs(A[max][k]))
					max = i;
			//row swap
			vector<precision> row_swap = A[max];
			A[max] = A[k];
			A[k] = row_swap;
			P.push_back(max);
		}
		if(complete)
		{//execute complete pivoting
			int max_r = k;
			int max_c = k;
			for(int i = k+1; i < n; i++)
				for(int j = k+1; j < n; j++)
					if(abs(A[i][j]) > abs(A[max_r][max_c]))
					{
						max_r = i;
						max_c = j;
					}
			//row swap
			vector<precision> row_swap = A[max_r];
			A[max_r] = A[k];
			A[k] = row_swap;
			for(int i = 0; i < n; i++)
			{//column swap
				precision col_swap = A[i][max_c];
				A[i][max_c] = A[i][k];
				A[i][k] = col_swap;
			}
			P.push_back(max_r);
			Q.push_back(max_c);
		}
		for(int i = k+1; i < n; i++)//compute l and write it over the first column of A
			if(abs(A[k][k]) < pow(10, -15))//warn the user that the pivot elements are too small
				throw runtime_error("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\nERROR: PIVOT ELEMENTS ARE TOO SMALL\n///////////////////////////////");
			else if(A[k][k])//if we are pivoting, this statement should never be false
				A[i][k] = A[i][k]/A[k][k];
			else//division by 0
				throw logic_error("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\nUNABLE TO FACTOR\n////////////////");
		//compute the action of l on the sub-matrix
		for(int i = k+1; i < n; i++)
			for(int j = k+1; j < n; j++)
				A[i][j] = A[i][j] - A[i][k] * A[k][j];
	}
	A.push_back(P);
	A.push_back(Q);
	return A;
}

/* solves a linear system LUx = b with modifications for pivoting where necessary
 * first solves the system Ly = b
 * then solves the system Ux = y
 *
 * LU = the LU-factorization of PAQ, with up to two extra rows of length n-1 appended storing information about P and Q for pivoting
 * b = the given vector in LUx = b
 */
vector<precision> solve(vector<vector<precision>> LU, vector<precision> b)
{
	int n = b.size();
	if(LU[n].size())//if partial pivoting or complete pivoting were performed
		b = permute_P(LU[n], b);
	for(int i = 1; i < n; i++)//solving L*y = b
		for(int j = i-1; j >= 0; j--)
			b[i] = b[i] - LU[i][j] * b[j];
	for(int i = n-1; i >= 0; i--)
	{//solving U*x = y
		for(int j = i+1; j < n; j++)
			b[i] = b[i] - LU[i][j] * b[j];
		b[i] = b[i] / LU[i][i];
	}
	if(LU[n+1].size())//if complete pivoting was performed
		b = permute_Q(LU[n+1], b);
	return b;
}
