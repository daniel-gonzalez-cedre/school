/*
 * Daniel Gonzalez
 * Florida State University Dept. of Mathematics
 */
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <math.h>
using namespace std;
#include "norms.h"
#include "linear_algebra.h"

#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

const precision π = M_PI;

vector<precision> F1(vector<precision> x){
	precision ξ = x[0];
	precision η = x[1];
	x[0] = pow(ξ, 2) + pow(η, 2) - 4;
	x[1] = exp(ξ) + η - 1;
	return x;
}

precision J1(vector<precision> x, int i){
	precision ξ = x[0];
	precision η = x[1];
	switch(i){
		case 1: return 2*η;
		case 2: return exp(ξ);
		case 3: return 1;
		default: return 2*ξ;
	}
}

vector<precision> F2(vector<precision> x){
	precision ξ = x[0];
	precision η = x[1];
	x[0] = sin(ξ*η)/2 - ξ/2 - η/(4*π);
	x[1] = (1 - 1/(4*π))*(exp(2*ξ) - exp(1)) - 2*exp(1)*ξ + exp(1)*η/π;
	return x;
}

precision J2(vector<precision> x, int i){
	precision ξ = x[0];
	precision η = x[1];
	switch(i){
		case 1: return ξ*cos(ξ*η)/2 - 1/(4*π);
		case 2: return (2 - 1/(2*π))*exp(2*ξ) - 2*exp(1);
		case 3: return exp(1)/π;
		default: return (η*cos(ξ*η) - 1)/2;
	}
}

vector<precision> F3(vector<precision> x){
	precision ξ = x[0];
	precision η = x[1];
	x[0] = (ξ + 3)*(pow(η, 3) - 7) + 18;
	x[1] = sin(η*exp(ξ) - 1);
	return x;
}

precision J3(vector<precision> x, int i){
	precision ξ = x[0];
	precision η = x[1];
	switch(i){
		case 1: return 3*pow(η, 2)*(ξ + 3);
		case 2: return η*exp(ξ)*cos(η*exp(ξ) - 1);
		case 3: return exp(ξ)*cos(η*exp(ξ) - 1);
		default: return pow(η, 3) - 7;
	}
}

vector<precision> newton(vector<precision> (*F)(vector<precision>), precision (*J)(vector<precision>, int), vector<precision> x, precision ε, int bound){
	int itr = 0;
	vector<precision> f = F(x);
	vector<vector<precision>> j(2);
	for(int i = 0; i < 2; i++)
		j[i] = vector<precision>(2);
	while(norm_inf(f) > ε && ++itr <= bound){
		j[0][0] = J(x, 0);
		j[0][1] = J(x, 1);
		j[1][0] = J(x, 2);
		j[1][1] = J(x, 3);
		x = difference(x, product(inverse2x2(j), f));
		f = F(x);
	}
	x.push_back(itr);
	return (itr <= bound) ? x : vector<precision>();
}

vector<precision> broyden(vector<precision> (*F)(vector<precision>), vector<vector<precision>> B, vector<precision> x, precision α, precision ε, int bound){
	int itr = 0;
	vector<precision> s, χ, φ, f = F(x);
	while(norm_inf(f) > ε && ++itr <= bound){
		χ = x;
		x = difference(x, scale(α, product(inverse2x2(B), f)));
		φ = F(x);
		s = difference(x, χ);
		B = sum(B, scale(1/pow(norm_L2(s), 2), outer_product(difference(difference(φ, f), product(B, s)), s)));
		f = φ;
	}
	x.push_back(itr);
	return (itr <= bound) ? x : vector<precision>();
}

vector<precision> jacobi(vector<precision> (*F)(vector<precision>), precision (*J)(vector<precision>, int), vector<precision> x, precision ε, int bound){
	int itr = 0;
	vector<precision> f = F(x);
	while(norm_inf(f) > ε && ++itr <= bound){
		vector<precision> χ = x;
		x[0] = x[0] - f[0]/J(χ, 0);
		x[1] = x[1] - f[1]/J(χ, 3);
		f = F(x);
	}
	x.push_back(itr);
	return (itr <= bound) ? x : vector<precision>();
}

vector<precision> gauss_seidel(vector<precision> (*F)(vector<precision>), precision (*J)(vector<precision>, int), vector<precision> x, precision ε, int bound){
	int itr = 0;
	vector<precision> f = F(x);
	while(norm_inf(f) > ε && ++itr <= bound){
		x[0] = x[0] - f[0]/J(x, 0);
		x[1] = x[1] - F(x)[1]/J(x, 3);
		f = F(x);
	}
	x.push_back(itr);
	return (itr <= bound) ? x : vector<precision>();
}

void test_ic(int t, precision ε, int bound, precision δ){
	vector<precision> root;
	vector<precision> x(2);
	vector<vector<precision>> J(2);
	ofstream file1, file2, file3;
	switch(t){
		case 1:
			file1.open("broyden1.txt");
			file2.open("broyden2.txt");
			file3.open("broyden3.txt");
			file1 << "root\tinitial\titerations" << endl;
			file2 << "root\tinitial\titerations" << endl;
			file3 << "root\tinitial\titerations" << endl;
			for(int i = 0; i < 2; i++)
				J[i] = vector<precision>(2);
			for(precision ξ = -4; ξ <= 4; ξ = ξ + δ){
				x[0] = ξ;
				for(precision η = -4; η <= 4; η = η + δ){
					x[1] = η;
					J[0][0] = J1(x, 0);
					J[0][1] = J1(x, 1);
					J[1][0] = J1(x, 2);
					J[1][1] = J1(x, 3);
					root = broyden(F1, J, x, 1, ε, bound);
					if(root.size() != 0
							&& to_string(root[0]) != "nan" && to_string(root[1]) != "nan"
							&& to_string(root[0]) != "inf" && to_string(root[1]) != "inf"
							&& to_string(root[0]) != "-inf" && to_string(root[1]) != "-inf")
						file1 << root[0] << " " << root[1] << "\t" << ξ << " "<< η << "\t" << root[2] << endl;
					J[0][0] = J2(x, 0);
					J[0][1] = J2(x, 1);
					J[1][0] = J2(x, 2);
					J[1][1] = J2(x, 3);
					root = broyden(F2, J, x, 1, ε, bound);
					if(root.size() != 0
							&& to_string(root[0]) != "nan" && to_string(root[1]) != "nan"
							&& to_string(root[0]) != "inf" && to_string(root[1]) != "inf"
							&& to_string(root[0]) != "-inf" && to_string(root[1]) != "-inf")
						file2 << root[0] << " " << root[1] << "\t" << ξ << " "<< η << "\t" << root[2] << endl;
					J[0][0] = J3(x, 0);
					J[0][1] = J3(x, 1);
					J[1][0] = J3(x, 2);
					J[1][1] = J3(x, 3);
					root = broyden(F3, J, x, 1, ε, bound);
					if(root.size() != 0
							&& to_string(root[0]) != "nan" && to_string(root[1]) != "nan"
							&& to_string(root[0]) != "inf" && to_string(root[1]) != "inf"
							&& to_string(root[0]) != "-inf" && to_string(root[1]) != "-inf")
						file3 << root[0] << " " << root[1] << "\t" << ξ << " "<< η << "\t" << root[2] << endl;
					cout << "ξ: " << ξ << "\tη: " << η << endl;
				}
			}
			break;
		case 2:
			file1.open("jacobi1.txt");
			file2.open("jacobi2.txt");
			file3.open("jacobi3.txt");
			file1 << "root\tinitial\titerations" << endl;
			file2 << "root\tinitial\titerations" << endl;
			file3 << "root\tinitial\titerations" << endl;
			for(precision ξ = -4; ξ <= 4; ξ = ξ + δ){
				x[0] = ξ;
				for(precision η = -4; η <= 4; η = η + δ){
					x[1] = η;
					root = jacobi(F1, J1, x, ε, bound);
					if(root.size() != 0
							&& to_string(root[0]) != "nan" && to_string(root[1]) != "nan"
							&& to_string(root[0]) != "inf" && to_string(root[1]) != "inf"
							&& to_string(root[0]) != "-inf" && to_string(root[1]) != "-inf")
						file1 << root[0] << " " << root[1] << "\t" << ξ << " "<< η << "\t" << root[2] << endl;
					root = jacobi(F2, J2, x, ε, bound);
					if(root.size() != 0
							&& to_string(root[0]) != "nan" && to_string(root[1]) != "nan"
							&& to_string(root[0]) != "inf" && to_string(root[1]) != "inf"
							&& to_string(root[0]) != "-inf" && to_string(root[1]) != "-inf")
						file2 << root[0] << " " << root[1] << "\t" << ξ << " "<< η << "\t" << root[2] << endl;
					root = jacobi(F3, J3, x, ε, bound);
					if(root.size() != 0
							&& to_string(root[0]) != "nan" && to_string(root[1]) != "nan"
							&& to_string(root[0]) != "inf" && to_string(root[1]) != "inf"
							&& to_string(root[0]) != "-inf" && to_string(root[1]) != "-inf")
						file3 << root[0] << " " << root[1] << "\t" << ξ << " "<< η << "\t" << root[2] << endl;
					cout << "ξ: " << ξ << "\tη: " << η << endl;
				}
			}
			break;
		case 3:
			file1.open("gauss_seidel1.txt");
			file2.open("gauss_seidel2.txt");
			file3.open("gauss_seidel3.txt");
			file1 << "root\tinitial\titerations" << endl;
			file2 << "root\tinitial\titerations" << endl;
			file3 << "root\tinitial\titerations" << endl;
			for(precision ξ = -4; ξ <= 4; ξ = ξ + δ){
				x[0] = ξ;
				for(precision η = -4; η <= 4; η = η + δ){
					x[1] = η;
					root = gauss_seidel(F1, J1, x, ε, bound);
					if(root.size() != 0
							&& to_string(root[0]) != "nan" && to_string(root[1]) != "nan"
							&& to_string(root[0]) != "inf" && to_string(root[1]) != "inf"
							&& to_string(root[0]) != "-inf" && to_string(root[1]) != "-inf")
						file1 << root[0] << " " << root[1] << "\t" << ξ << " "<< η << "\t" << root[2] << endl;
					root = gauss_seidel(F2, J2, x, ε, bound);
					if(root.size() != 0
							&& to_string(root[0]) != "nan" && to_string(root[1]) != "nan"
							&& to_string(root[0]) != "inf" && to_string(root[1]) != "inf"
							&& to_string(root[0]) != "-inf" && to_string(root[1]) != "-inf")
						file2 << root[0] << " " << root[1] << "\t" << ξ << " "<< η << "\t" << root[2] << endl;
					root = gauss_seidel(F3, J3, x, ε, bound);
					if(root.size() != 0
							&& to_string(root[0]) != "nan" && to_string(root[1]) != "nan"
							&& to_string(root[0]) != "inf" && to_string(root[1]) != "inf"
							&& to_string(root[0]) != "-inf" && to_string(root[1]) != "-inf")
						file3 << root[0] << " " << root[1] << "\t" << ξ << " "<< η << "\t" << root[2] << endl;
					cout << "ξ: " << ξ << "\tη: " << η << endl;
				}
			}
			break;
		default:
			file1.open("newton1.txt");
			file2.open("newton2.txt");
			file3.open("newton3.txt");
			file1 << "root\tinitial\titerations" << endl;
			file2 << "root\tinitial\titerations" << endl;
			file3 << "root\tinitial\titerations" << endl;
			for(precision ξ = -4; ξ <= 4; ξ = ξ + δ){
				x[0] = ξ;
				for(precision η = -4; η <= 4; η = η + δ){
					x[1] = η;
					root = newton(F1, J1, x, ε, bound);
					if(root.size() != 0
							&& to_string(root[0]) != "nan" && to_string(root[1]) != "nan"
							&& to_string(root[0]) != "inf" && to_string(root[1]) != "inf"
							&& to_string(root[0]) != "-inf" && to_string(root[1]) != "-inf")
						file1 << root[0] << " " << root[1] << "\t" << ξ << " "<< η << "\t" << root[2] << endl;
					root = newton(F2, J2, x, ε, bound);
					if(root.size() != 0
							&& to_string(root[0]) != "nan" && to_string(root[1]) != "nan"
							&& to_string(root[0]) != "inf" && to_string(root[1]) != "inf"
							&& to_string(root[0]) != "-inf" && to_string(root[1]) != "-inf")
						file2 << root[0] << " " << root[1] << "\t" << ξ << " "<< η << "\t" << root[2] << endl;
					root = newton(F3, J3, x, ε, bound);
					if(root.size() != 0
							&& to_string(root[0]) != "nan" && to_string(root[1]) != "nan"
							&& to_string(root[0]) != "inf" && to_string(root[1]) != "inf"
							&& to_string(root[0]) != "-inf" && to_string(root[1]) != "-inf")
						file3 << root[0] << " " << root[1] << "\t" << ξ << " "<< η << "\t" << root[2] << endl;
					cout << "ξ: " << ξ << "\tη: " << η << endl;
				}
			}
	}
	file1.close();
	file2.close();
	file3.close();
}

void test_compare(vector<vector<precision>> x, int bound){
	vector<vector<precision>> J(2);
	for(int i = 0; i < 2; i++)
		J[i] = vector<precision>(2);
	ofstream file1, file2, file3;
	file1.open("compare1.txt");
	file2.open("compare2.txt");
	file3.open("compare3.txt");
	for(precision ε = pow(10, -1); ε >= pow(10, -8); ε = ε/10){
		J[0][0] = J1(x[0], 0);
		J[0][1] = J1(x[0], 1);
		J[1][0] = J1(x[0], 2);
		J[1][1] = J1(x[0], 3);
		file1 << newton(F1, J1, x[0], ε, bound)[2] << " ";
		file1 << broyden(F1, J, x[0], 1, ε, bound)[2] << " ";
		file1 << jacobi(F1, J1, x[0], ε, bound)[2] << " ";
		file1 << gauss_seidel(F1, J1, x[0], ε, bound)[2] << endl;
	}
	for(precision ε = pow(10, -1); ε >= pow(10, -8); ε = ε/10){
		J[0][0] = J2(x[1], 0);
		J[0][1] = J2(x[1], 1);
		J[1][0] = J2(x[1], 2);
		J[1][1] = J2(x[1], 3);
		file2 << newton(F2, J2, x[1], ε, bound)[2] << " ";
		file2 << broyden(F2, J, x[1], 1, ε, bound)[2] << " ";
		file2 << jacobi(F2, J2, x[1], ε, bound)[2] << " ";
		file2 << gauss_seidel(F2, J2, x[1], ε, bound)[2] << endl;
	}
	for(precision ε = pow(10, -1); ε >= pow(10, -8); ε = ε/10){
		J[0][0] = J3(x[2], 0);
		J[0][1] = J3(x[2], 1);
		J[1][0] = J3(x[2], 2);
		J[1][1] = J3(x[2], 3);
		file3 << newton(F3, J3, x[2], ε, bound)[2] << " ";
		file3 << broyden(F3, J, x[2], 1, ε, bound)[2] << " ";
		file3 << jacobi(F3, J3, x[2], ε, bound)[2] << " ";
		file3 << gauss_seidel(F3, J3, x[2], ε, bound)[2] << endl;
	}
	file1.close();
	file2.close();
	file3.close();
}

void test_empirical(vector<vector<precision>> x){
	ofstream file1, file2, file3, file4;
	file1.open("empirical_newton.txt");
	file2.open("empirical_broyden.txt");
	file3.open("empirical_jacobi.txt");
	file4.open("empirical_gauss-seidel.txt");
	vector<precision> r(2);
	vector<precision> temp(3);
	vector<vector<precision>> J(2);
	for(int i = 0; i < 2; i++)
		J[i] = vector<precision>(2);
	file1 << x[0][0] << " " << x[0][1] << " " << norm_L2(F2(x[0])) << endl;
	for(int i = 1; i <= 5; i++){
		temp = newton(F2, J2, x[0], 0, i);
		r[0] = temp[0];
		r[1] = temp[1];
		file1 << r[0] << " " << r[1] << " " << norm_L2(F2(r)) << endl;
	}
	file2 << x[1][0] << " " << x[1][1] << " " << norm_L2(F3(x[1])) << endl;
	for(int i = 1; i <= 6; i++){
		J[0][0] = J3(x[1], 0);
		J[0][1] = J3(x[1], 1);
		J[1][0] = J3(x[1], 2);
		J[1][1] = J3(x[1], 3);
		temp = broyden(F3, J, x[1], 1, 0, i);
		r[0] = temp[0];
		r[1] = temp[1];
		file2 << r[0] << " " << r[1] << " " << norm_L2(F3(r)) << endl;
	}
	file3 << x[0][0] << " " << x[0][1] << " " << norm_L2(F2(x[0])) << endl;
	for(int i = 1; i <= 15; i++){
		temp = jacobi(F2, J2, x[0], 0, i);
		r[0] = temp[0];
		r[1] = temp[1];
		file3 << r[0] << " " << r[1] << " " << norm_L2(F2(r)) << endl;
	}
	file4 << x[0][0] << " " << x[0][1] << " " << norm_L2(F2(x[0])) << endl;
	for(int i = 1; i <= 7; i++){
		temp = gauss_seidel(F2, J2, x[0], 0, i);
		r[0] = temp[0];
		r[1] = temp[1];
		file4 << r[0] << " " << r[1] << " " << norm_L2(F2(r)) << endl;
	}
	file1.close();
	file2.close();
	file3.close();
	file4.close();
}

int main(int argc, char* argv[]){
	for(int i = 0; i < 4; i++)
		test_ic(i, pow(10, -4), pow(10, 4), pow(10, -1));
	vector<vector<precision>> x(3);
	x[0].push_back(-4);
	x[0].push_back(-3.8);
	x[1].push_back(-4);
	x[1].push_back(0);
	x[2].push_back(4);
	x[2].push_back(4);
	test_compare(x, pow(10, 4));
	x[0][0] = 0.4;
	x[0][1] = 3;
	x[1][0] = -0.5;
	x[1][1] = 1.4;
	test_empirical(x);

	return 0;
}
