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

#include "norms.h"
#include "matrix.h"
#include "code.h"

//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

const precision PI = M_PI;

int main(int argc, char* argv[])
{
	int n = 1000;
	ofstream data;
	data.open("data");
	data << "n: " << n << endl << endl;

	//test 1
	vector<vector<precision>> L = generate_unit_triangular(n);
	vector<vector<precision>> U = generate_upper_triangular(n);
	vector<vector<precision>> ALU = product(L, U);
	vector<vector<precision>> LU_none = factor(ALU, 0, 0);
	vector<vector<precision>> LU_partial = factor(ALU, 1, 0);
	vector<vector<precision>> LU_complete = factor(ALU, 0, 1);
	data << "Test 1: generate L and U, compute A <- LU, and factor A" << endl;
	data << "-------" << endl;
	data << "factorization relative error without pivoting using L1 Norm: " << factorization_accuracy(ALU, LU_none, ALU, norm_1) << endl;
	data << "factorization relative error with partial pivoting using L1 Norm: " << factorization_accuracy(permute_P(LU_partial[n], ALU), LU_partial, ALU, norm_1) << endl;
	data << "factorization relative error with complete pivoting using L1 Norm: " << factorization_accuracy(permute_Q(LU_complete[n+1], permute_P(LU_complete[n], ALU)), LU_complete, ALU, norm_1) << endl;
	data << "-------" << endl;
	data << "factorization relative error without pivoting using Infinity Norm: " << factorization_accuracy(ALU, LU_none, ALU, norm_infinity) << endl;
	data << "factorization relative error with partial pivoting using Infinity Norm: " << factorization_accuracy(permute_P(LU_partial[n], ALU), LU_partial, ALU, norm_infinity) << endl;
	data << "factorization relative error with complete pivoting using Infinity Norm: " << factorization_accuracy(permute_Q(LU_complete[n+1], permute_P(LU_complete[n], ALU)), LU_complete, ALU, norm_infinity) << endl;
	data << "-------" << endl;
	data << "factorization relative error without pivoting using Frobenius Norm: " << factorization_accuracy(ALU, LU_none, ALU, norm_frobenius) << endl;
	data << "factorization relative error with partial pivoting using Frobenius Norm: " << factorization_accuracy(permute_P(LU_partial[n], ALU), LU_partial, ALU, norm_frobenius) << endl;
	data << "factorization relative error with complete pivoting using Frobenius Norm: " << factorization_accuracy(permute_Q(LU_complete[n+1], permute_P(LU_complete[n], ALU)), LU_complete, ALU, norm_frobenius) << endl;
	data << endl;

	//test 2
	vector<vector<precision>> R = generate_random_nonsingular(n);
	vector<vector<precision>> LU_R_none = factor(R, 0, 0);
	vector<vector<precision>> LU_R_partial = factor(R, 1, 0);
	vector<vector<precision>> LU_R_complete = factor(R, 0, 1);
	data << "Test 2: generate and factor a random, diagonally-dominant matrix" << endl;
	data << "-------" << endl;
	data << "factorization relative error without pivoting using L1 Norm: " << factorization_accuracy(product(LU_R_none), LU_R_none, R, norm_1) << endl;
	data << "factorization relative error with partial pivoting using L1 Norm: " << factorization_accuracy(product(LU_R_partial), LU_R_partial, R, norm_1) << endl;
	data << "factorization relative error with complete pivoting using L1 Norm: " << factorization_accuracy(product(LU_R_complete), LU_R_complete, R, norm_1) << endl;
	data << "-------" << endl;
	data << "factorization relative error without pivoting using Infinity Norm: " << factorization_accuracy(product(LU_R_none), LU_R_none, R, norm_infinity) << endl;
	data << "factorization relative error with partial pivoting using Infinity Norm: " << factorization_accuracy(product(LU_R_partial), LU_R_partial, R, norm_infinity) << endl;
	data << "factorization relative error with complete pivoting using Infinity Norm: " << factorization_accuracy(product(LU_R_complete), LU_R_complete, R, norm_infinity) << endl;
	data << "-------" << endl;
	data << "factorization relative error without pivoting using Frobenius Norm: " << factorization_accuracy(product(LU_R_none), LU_R_none, R, norm_frobenius) << endl;
	data << "factorization relative error with partial pivoting using Frobenius Norm: " << factorization_accuracy(product(LU_R_partial), LU_R_partial, R, norm_frobenius) << endl;
	data << "factorization relative error with complete pivoting using Frobenius Norm: " << factorization_accuracy(product(LU_R_complete), LU_R_complete, R, norm_frobenius) << endl;
	data << endl;

	//test task 3
	vector<precision> x = generate_random_vector(n);
	vector<vector<precision>> A = generate_random_nonsingular(n);
	vector<precision> b = product(A, x);
	vector<precision> x_none = solve(factor(A, 0, 0), b);
	vector<precision> x_partial = solve(factor(A, 1, 0), b);
	vector<precision> x_complete = solve(factor(A, 0, 1), b);
	data << "Test 3: solve system Ax = b given A and x, generating b <- Ax" << endl;
	data << "-------" << endl;
	data << "solution relative error without pivoting using L1 Norm: " << solution_accuracy(x, x_none, norm_1) << endl;
	data << "solution relative error with partial pivoting using L1 Norm: " << solution_accuracy(x, x_partial, norm_1) << endl;
	data << "solution relative error with complete pivoting using L1 Norm: " << solution_accuracy(x, x_complete, norm_1) << endl;
	data << "-------" << endl;
	data << "solution relative error without pivoting using Infinity Norm: " << solution_accuracy(x, x_none, norm_infinity) << endl;
	data << "solution relative error with partial pivoting using Infinity Norm: " << solution_accuracy(x, x_partial, norm_infinity) << endl;
	data << "solution relative error with complete pivoting using Infinity Norm: " << solution_accuracy(x, x_complete, norm_infinity) << endl;
	data << "-------" << endl;
	data << "solution relative error without pivoting using Frobenius Norm: " << solution_accuracy(x, x_none, norm_frobenius) << endl;
	data << "solution relative error with partial pivoting using Frobenius Norm: " << solution_accuracy(x, x_partial, norm_frobenius) << endl;
	data << "solution relative error with complete pivoting using Frobenius Norm: " << solution_accuracy(x, x_complete, norm_frobenius) << endl;
	data << "|||||||" << endl;
	data << "residual relative error without pivoting using L1 Norm: " << residual_accuracy(b, A, x_none, norm_1) << endl;
	data << "residual relative error with partial pivoting using L1 Norm: " << residual_accuracy(b, A, x_partial, norm_1) << endl;
	data << "residual relative error with complete pivoting using L1 Norm: " << residual_accuracy(b, A, x_complete, norm_1) << endl;
	data << "-------" << endl;
	data << "residual relative error without pivoting using Infinity Norm: " << residual_accuracy(b, A, x_none, norm_infinity) << endl;
	data << "residual relative error with partial pivoting using Infinity Norm: " << residual_accuracy(b, A, x_partial, norm_infinity) << endl;
	data << "residual relative error with complete pivoting using Infinity Norm: " << residual_accuracy(b, A, x_complete, norm_infinity) << endl;
	data << "-------" << endl;
	data << "residual relative error without pivoting using Frobenius Norm: " << residual_accuracy(b, A, x_none, norm_frobenius) << endl;
	data << "residual relative error with partial pivoting using Frobenius Norm: " << residual_accuracy(b, A, x_partial, norm_frobenius) << endl;
	data << "residual relative error with complete pivoting using Frobenius Norm: " << residual_accuracy(b, A, x_complete, norm_frobenius) << endl;
	data << endl;

	//test task 4
	vector<vector<precision>> Z = generate_random_nonsingular(n);
	for(int i = 0; i < n; i++)
		Z[i][i] = 0;
	vector<vector<precision>> LU_Z_partial = factor(Z, 1, 0);
	vector<vector<precision>> LU_Z_complete = factor(Z, 0, 1);
	data << "Test 4: generate a matrix that requires pivoting and factor it" << endl;
	data << "-------" << endl;
	data << "factorization relative error with partial pivoting using L1 Norm: " << factorization_accuracy(permute_P(LU_Z_partial[n], Z), LU_Z_partial, Z, norm_1) << endl;
	data << "factorization relative error with complete pivoting using L1 Norm: " << factorization_accuracy(permute_Q(LU_Z_complete[n+1], permute_P(LU_Z_complete[n], Z)), LU_Z_complete, Z, norm_1) << endl;
	data << "-------" << endl;
	data << "factorization relative error with partial pivoting using Infinity Norm: " << factorization_accuracy(permute_P(LU_Z_partial[n], Z), LU_Z_partial, Z, norm_infinity) << endl;
	data << "factorization relative error with complete pivoting using Infinity Norm: " << factorization_accuracy(permute_Q(LU_Z_complete[n+1], permute_P(LU_Z_complete[n], Z)), LU_Z_complete, Z, norm_infinity) << endl;
	data << "-------" << endl;
	data << "factorization relative error with partial pivoting using Frobenius Norm: " << factorization_accuracy(permute_P(LU_Z_partial[n], Z), LU_Z_partial, Z, norm_frobenius) << endl;
	data << "factorization relative error with complete pivoting using Frobenius Norm: " << factorization_accuracy(permute_Q(LU_Z_complete[n+1], permute_P(LU_Z_complete[n], Z)), LU_Z_complete, Z, norm_frobenius) << endl;
	data << endl;

	//test task 5
	vector<precision> b_given = generate_random_vector(n);
	vector<vector<precision>> A_given = generate_random_nonsingular(n);
	vector<precision> computed_x_none = solve(factor(A_given, 0, 0), b_given);
	vector<precision> computed_x_partial = solve(factor(A_given, 1, 0), b_given);
	vector<precision> computed_x_complete = solve(factor(A_given, 0, 1), b_given);
	vector<precision> residual_none = product(A, computed_x_none);
	vector<precision> residual_partial = product(A, computed_x_partial);
	vector<precision> residual_complete = product(A, computed_x_complete);
	data << "Test 5: solve linear system Ax = b given A and b" << endl;
	data << "-------" << endl;
	data << "residual relative error without pivoting using L1 Norm: " << residual_accuracy(b_given, A_given, computed_x_none, norm_1) << endl;
	data << "residual relative error with partial pivoting using L1 Norm: " << residual_accuracy(b_given, A_given, computed_x_partial, norm_1) << endl;
	data << "residual relative error with complete pivoting using L1 Norm: " << residual_accuracy(b_given, A_given, computed_x_complete, norm_1) << endl;
	data << "-------" << endl;
	data << "residual relative error without pivoting using Infinity Norm: " << residual_accuracy(b_given, A_given, computed_x_none, norm_infinity) << endl;
	data << "residual relative error with partial pivoting using Infinity Norm: " << residual_accuracy(b_given, A_given, computed_x_partial, norm_infinity) << endl;
	data << "residual relative error with complete pivoting using Infinity Norm: " << residual_accuracy(b_given, A_given, computed_x_complete, norm_infinity) << endl;
	data << "-------" << endl;
	data << "residual relative error without pivoting using Frobenius Norm: " << residual_accuracy(b_given, A_given, computed_x_none, norm_frobenius) << endl;
	data << "residual relative error with partial pivoting using Frobenius Norm: " << residual_accuracy(b_given, A_given, computed_x_partial, norm_frobenius) << endl;
	data << "residual relative error with complete pivoting using Frobenius Norm: " << residual_accuracy(b_given, A_given, computed_x_complete, norm_frobenius) << endl;
	data << endl;

	data.close();
	return 0;
}
