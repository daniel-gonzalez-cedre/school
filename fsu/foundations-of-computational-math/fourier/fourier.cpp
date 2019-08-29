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

//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

const precision PI = M_PI;
const complex<precision> I(0, 1);
const complex<precision> NEG(-1, 0);
const complex<precision> ROOT2(1/sqrt(2), 0);

/* generates a random square "image" of size nxn
 * O(n^2) time complexity
 * O(n^2) space complexity
 *
 * n = the row and column dimension of the resultant matrix image
 * d = the divisor
 */
vector<vector<complex<precision>>> generate(int n, int max_range, precision divisor){
	vector<vector<complex<precision>>> F(n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			F[i].push_back(complex<precision>((rand() % max_range) / divisor, (rand() % max_range) / divisor));
	return F;
}

/* compresses the frequencies of a DFT-transformed matrix
 * O(n) time complexity
 * O(1) space complexity (in place)
 *
 * F = the matrix to be compressed
 * k = how many rows/columns to compress to zero
 */
vector<vector<complex<precision>>> frequency_compress(vector<vector<complex<precision>>> F, int k){
	int n = F.size();
	for(int i = 1; i <= k; i++)
		for(int j = 0; j < n; j++){
			F[n-i][j] = complex<precision>(0, 0);
			F[j][n-i] = complex<precision>(0, 0);
		}
	return F;
}

/* compresses the elements of a complex-valued matrix which fall below a minimum threshold
 * O(n^2) time complexity
 * O(1) space complexity (in place)
 *
 * F = the matrix to be compressed
 * threshold = the minimum non-zero value permissible in the compressed matrix
 */
vector<vector<complex<precision>>> compress_time(vector<vector<complex<precision>>> T, precision threshold){
	int n = T.size();
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(abs(T[i][j]) < threshold)
				T[i][j] = complex<precision>(0, 0);
	return T;
}

/* computes the (inverse) Discrete Fourier Transform of an input time-series (or frequency) f
 * O(n^2) time complexity
 * O(n) space complexity
 *
 * f = a vector of complex numbers representing the time-series (or frequency) to be transformed of size 2^n
 * inverse = an integer flag which, when set, computes the inverse transform
 */
vector<complex<precision>> dft(vector<complex<precision>> f, int inverse){
	int n = f.size();
	complex<precision> theta(2 * PI/n, 0);
	complex<precision> scale(1/sqrt(n), 0);
	vector<complex<precision>> fourier;
	for(int i = 0; i < n; i++){//Horner's Rule suggested by colleague, as opposed to naïve monomial evaluation
		complex<precision> sum = f[n-1];
		complex<precision> exponent(i, 0);
		complex<precision> mu = exp(exponent * NEG * I * theta);
		if(inverse)
			mu = conj(mu);
		for(int j = n-2; j >= 0; j--)
			sum = sum * mu + f[j];
		fourier.push_back(scale * sum);
	}
	return fourier;
}

/* recursively computes the (inverse) Fast Fourier Transform of an input time-series (or frequency) f
 * O(n log(n)) time complexity
 * O(n log(n)) space complexity
 *
 * f = a vector of complex numbers representing the time-series (or frequency) to be transformed of size 2^n
 * inverse = an integer flag which, when set, computes the inverse transform
 */
vector<complex<precision>> fft(vector<complex<precision>> f, int inverse){
	int n = f.size();
	if(n == 2)//base case
		return dft(f, inverse);
	vector<complex<precision>> f_even;
	vector<complex<precision>> f_odd;
	for(int i = 0; i < n; i++)//sorting the input f into f_even and f_odd
        (i%2 == 0) ? f_even.push_back(f[i]) : f_odd.push_back(f[i]);
	f_even = fft(f_even, inverse);
	f_odd = fft(f_odd, inverse);
	complex<precision> theta(2 * PI/n, 0);
	for(int i = 0; i < n; i++){//combine the recursive solutions from dim n/2 to build the solution for dim n
		complex<precision> exponent(i, 0);
		complex<precision> mu = exp(exponent * NEG * I * theta);
		if(inverse)
			mu = conj(mu);
		f[i] = ROOT2 * (f_even[i%(n/2)] + mu * f_odd[i%(n/2)]);
	}
	return f;
}

/* computes the 2-dimensional (i)FFT of an input matrix F
 * O(n^2 log(n)) time complexity
 * O(n) space complexity
 *
 * F = a matrix of complex numbers representing the time-series (or frequency) to be transformed of dimension 2^n
 * inverse = an integer flag which, when set, computes the inverse transform
 */
vector<vector<complex<precision>>> two_fft(vector<vector<complex<precision>>> F, int inverse){
	int n = F[0].size();
	for(int i = 0; i < n; i++)//compute the (i)FFT of the rows
		F[i] = fft(F[i], inverse);
	for(int i = 0; i < n; i++){//compute the (i)FFT of the columns
		vector<complex<precision>> F_col;
		for(int j = 0; j < n; j++)//copy the ith column into a new row vector
			F_col.push_back(F[j][i]);
		F_col = fft(F_col, inverse);
		for(int j = 0; j < n; j++)//rewrite the transformed column back into its original place
			F[j][i] = F_col[j];
	}
	return F;
}

/* finds the solution x to a linear system Cx = b given a circulant matrix C by factoring C = F^H Gamma F
 * this is equivalent to solving x^TC^T = b^T where C^T is circulant if and only if C is circulant
 * O(n^2) time complexity
 * O(1) space complexity (disregarding calls to fft(...))
 *
 * C = a complex of dimension n which determines a complex circulant matrix of dimension n
 * b = a complex vector of length n
 */
vector<complex<precision>> solve(vector<complex<precision>> C, vector<complex<precision>> b){
	b = fft(b, 0);
	int n = C.size();
	complex<precision> theta(2 * PI/n, 0);
	for(int i = 0; i < n; i++){//compute Gamma inverse and multiply it by b using Horner's Rule
		complex<precision> sum = C[n-1];
		complex<precision> exponent(i, 0);
		complex<precision> omega = exp(exponent * I * theta);
		for(int j = n-2; j >= 0; j--)
			sum = sum * omega + C[j];
		b[i] = b[i] / sum;
	}
	b = fft(b, 1);
	return b;
}

/* finds the solution I to a linear system M = C^TIC given a matrix M and a circulant matrix C
 * this is done by first solving M = LC for L and then solving L = IC for I
 * O(n^3) time complexity
 * O(n^2) space complexity
 *
 * M = the blurred image matrix
 * C = the first row of the circulant matrix used to blur the solution
 */
vector<vector<complex<precision>>> focus(vector<vector<complex<precision>>> M, vector<complex<precision>> C){
	int n = C.size();
	vector<vector<complex<precision>>> I(n);
	vector<vector<complex<precision>>> L(n);
	vector<complex<precision>> CT;
	CT.push_back(C[0]);
	for(int i = n-1; i > 0; i--)//find the transpose of C by downshifting its characteristic first row
		CT.push_back(C[i]);
	for(int i = 0; i < n; i++)//solving M = LC by rows
		L[i] = solve(CT, M[i]);
	for(int i = 0; i < n; i++){//solving L = C^TI by columns
		vector<complex<precision>> L_col;
		for(int j = 0; j < n; j++)//copy the ith column into a new row vector
			L_col.push_back(L[j][i]);
		vector<complex<precision>> I_col = solve(CT, L_col);
		for(int j = 0; j < n; j++)//rewrite the solved column back into the solution matrix
			I[j].push_back(I_col[j]);
	}
	return I;
}

int main(int argc, char* argv[]){
	int n = pow(2, 9);
	clock_t start;
	clock_t end;

	//INPUT the BLURRED image M
	cout << "Reading in the blurry image..." << endl;
	start = clock();
	vector<vector<complex<precision>>> M(n);
	ifstream inputM("blurred.txt");
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			precision m;
			inputM >> m;
			M[i].push_back(complex<precision>(m, 0));
		}
	inputM.close();
	end = clock();
	cout << "done. " << end - start << endl;

	//INPUT the CIRCULANT matrix row C
	cout << "Reading in the circulant row..." << endl;
	start = clock();
	vector<complex<precision>> C;
	ifstream inputC("circulant.txt");
	for(int i = 0; i < n; i++){
		precision c;
		inputC >> c;
		C.push_back(complex<precision>(c, 0));
	}
	inputC.close();
	end = clock();
	cout << "done. " << end - start << endl;

	//OUTPUT the FOCUSED image I
	cout << "Focussing the source image..." << endl;
	ofstream focused;
	focused.open("focused");
	start = clock();
	vector<vector<complex<precision>>> I = focus(M, C);
	end = clock();
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			focused << abs(I[i][j]) << " ";
		focused << endl;
	}
	focused.close();
	cout << "done. " << end - start << endl;

	return 0;
}
