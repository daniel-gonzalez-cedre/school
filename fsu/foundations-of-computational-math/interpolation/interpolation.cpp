/*
 * Daniel Gonzalez
 * Florida State University Dept. of Mathematics
 */
#include <iostream>
#include <fstream>
#include <limits>
#include <math.h>
using namespace std;

//precision is set to single by default
//use the g++ directive -DDOUBLE=1 at compile time to set precision from single to double
#ifdef DOUBLE
typedef double precision;
#else
typedef float precision;
#endif

//the first function given in the problem statement
precision function1(precision alpha, precision x){return abs(alpha*x)+(x/2)-(x*x);}

//the first derivative of function1
precision dfunction1(precision alpha, precision x)
{
	if(x > 0){return abs(alpha)+(1.0/2)-2*x;}
	if(x < 0){return -abs(alpha)+(1.0/2)-2*x;}
	return 0;
}

//the second derivative of function1
precision ddfunction1(precision alpha, precision x){return -2;}

//the second function given in the problem statement
precision function2(precision alpha, precision x){return 1/(1+(alpha*x*x));}

//the first derivative of function2
precision dfunction2(precision alpha, precision x){return -(2*alpha*x)/pow(alpha*x*x+1, 2);}

//the second derivative of function2
precision ddfunction2(precision alpha, precision x){return (2*alpha)*(3*alpha*x*x-1)/pow(alpha*x*x+1, 3);}

/*	computes the nth divided differences and all previous divided differences along the left path
 *	n is the largest degree of the divided differences computed
 *	O(n) space complexity
 *	O(n^2) time complexity
 *
 *	n = degree of divided difference; number of mesh points
 *	xmesh = the mesh of x values
 *	ymesh = the mesh of y values
 *	div_dif = an empty array to store the divided differences computed
 */
void divided_differences(int n, precision* xmesh, precision* ymesh, precision* div_dif)
{
	int k = 1;
	for(int i = 0; i < n; i++){div_dif[i] = ymesh[i];}
	for(int i = 0; i < n-1; i++)
	{
		for(int j = n-1; j > i; j = j-1){div_dif[j] = (div_dif[j]-div_dif[j-1])/(xmesh[j]-xmesh[j-k]);}
		k = k+1;
	}
}

/*	computes the newton interpolating polynomial on an arbitrary mesh of x and y values evaluated at x
 *	no assumptions are made about the mesh
 *	O(n) space complexity {storing the divided differences}
 *	O(n^2) time complexity {including the O(n^2) time complexity of computing the divided differences}
 *
 *	n = number of mesh points; the degree of the newton interpolating polynomial + 1
 *	xmesh = the mesh of x values
 *	ymesh = the mesh of y values
 *	x = where we evaluate the polynomial
 */
precision newton(int n, precision* xmesh, precision* ymesh, precision x)
{
	precision result = 0;
	precision div_dif[n];
	divided_differences(n, xmesh, ymesh, div_dif);
	for(int i = 0; i < n; i++)
	{
		precision prod = 1;
		for(int j = 1; j <= i; j++){prod = prod*(x-xmesh[j-1]);}
		result = result+div_dif[i]*prod;
	}
	return result;
}

/*	a simple recursive function to compute n!
 *	O(1) space complexity {discounting the n calls made to this function on the function stack; otherwise O(n) space complexity}
 *	O(n) time complexity
 *
 *	n = some number whose factorial we would like to compute
 */
long factorial(long n)
{
	if(n < 0){return 0;}
	if(n == 1 || n == 0){return 1;}
	return n*factorial(n-1);
}

/*	a simple factorial computation of n choose k
 *	O(1) space complexity
 *	O(n) time complexity {due to computing the three factorials; could be sped up by simplifying n!/(n-k)!}
 *
 *	n, k = some numbers who we'd like to compute n choose k for
 */
long choose(long n, long k){return factorial(n)/(factorial(n-k)*factorial(k));}

/*	computes the bernstein polynomial of degree on the interval [lower, upper] evaluated at x
 *	the mesh of y values is assumed to have been generated from a uniform mesh of x values
 *	O(n) space complexity
 *	O(n^2) time complexity {evaluation, choose}
 *
 *	n = degree of the bernstein polynomial; number of y values in the y mesh
 *	lower = lower bound of the interval
 *	upper = upper bound of the interval
 *	ymesh = mesh of y values of the function to approximate computed based on a uniform x mesh over [lower, upper]
 *	x = place to evaluate the bernstein polynomial
 */
precision bernstein(int n, precision lower, precision upper, precision* ymesh, precision x)
{
	precision result = 0;
	precision y = (x-lower)/(upper-lower);//biject x from the interval [lower, upper] to the interval [0, 1]
	for(int i = 0; i <= n; i++){result = result+ymesh[i]*choose(n, i)*pow(y, i)*pow(1-y, n-i);}
	return result;
}

/*	a simple increasing-order mergesort implementation
 *	modified to move the y mesh corresponding to the x mesh as the x mesh is sorted
 *	O(n) space complexity {O(log(n)) space on the function stack for recursive calls, O(n) space to store the lists}
 *	O(n*log(n)) time complexity
 *
 *	n = size of the xmesh array
 *	xmesh = list we wish to sort
 *	ymesh = list related to xmesh whose relative ordering must be preserved
 */
void sort(int n, precision* xmesh, precision* ymesh)
{
	if(n == 1){return;}
	if(n == 2)
	{
		if(xmesh[0] > xmesh[1])
		{
			precision temp = xmesh[0];
			xmesh[0] = xmesh[1];
			xmesh[1] = temp;
			temp = ymesh[0];
			ymesh[0] = ymesh[1];
			ymesh[1] = temp;
		}
		return;
	}
	int m = n/2;
	precision left_xmesh[m], left_ymesh[m];
	precision right_xmesh[n-m], right_ymesh[n-m];
	for(int i = 0; i < m; i++){left_xmesh[i] = xmesh[i], left_ymesh[i] = ymesh[i];}
	for(int i = m; i < n; i++){right_xmesh[i-m] = xmesh[i], right_ymesh[i-m] = ymesh[i];}
	sort(m, left_xmesh, left_ymesh);
	sort(n-m, right_xmesh, right_ymesh);
	int i= 0, j = 0, k = 0;
	while(i < m && j < n-m)
	{
		if(left_xmesh[i] <= right_xmesh[j]){xmesh[k] = left_xmesh[i], ymesh[k++] = left_ymesh[i++];}
		else{xmesh[k] = right_xmesh[j], ymesh[k++] = right_ymesh[j++];}
	}
	for(; i < m; i++){xmesh[k] = left_xmesh[i], ymesh[k++] = left_ymesh[i];}
	for(; j < n-m; j++){xmesh[k] = right_xmesh[j], ymesh[k++] = right_ymesh[j];}
}

/*	a simple binary search implementation
 *	modified to return the greatest list element less than or equal to the point we seek
 *	O(n) space complexity {storing the list to search through}
 *	O(log(n)) time complexity
 *
 *	n = size of the list to search
 *	mesh = an increasingly-sorted list
 *	x = the element we wish to find
 */
int search(int n, precision* mesh, precision x)
{
	if(x < mesh[0] || x > mesh[n-1]){cout << "Your point " << x << " is not within the specified interpolation interval." << endl; return -1;}
	int index = (n-1)/2;
	while(x < mesh[index] || mesh[index+1] <= x)
	{
		if(x < mesh[index]){index = index - (index+1)/2;}
		else{index = index + (index+1)/2;}
		if(mesh[index] == x){return index;}
	}
	return index;
}

//d must divide n - 1
/*	computes the piecewise polynomial interpolation for a given mesh of x and y values and evaluates at x
 *	no assumptions are made about the mesh
 *	the degree d must divide n-1; otherwise, we can not interpolate
 *	O(n) space complexity
 *	O(nlog(n)) + O(log(n)) time complexity {preprocessing; sort, search}
 *	O(n^2) time complexity {evaluation using newton}
 *	
 *	d = the degree of each piecewise polynomial used for interpolation
 *	n = the number of points to interpolate
 *	xmesh = the mesh of x values
 *	ymesh = the mesh of y values
 *	x = the place we evaluate the polynomial
 */
precision piecewise(int d, int n, precision* xmesh, precision* ymesh, precision x)
{
	sort(n, xmesh, ymesh);
	int index = search(n, xmesh, x);
	if(index == n-1){index = index-d;}
	else{index = index-(index%d);}
	precision newton_xmesh[d+1];
	precision newton_ymesh[d+1];
	for(int i = 0; i <= d; i++){newton_xmesh[i] = xmesh[index+i];}
	for(int i = 0; i <= d; i++){newton_ymesh[i] = ymesh[index+i];}
	return newton(d+1, newton_xmesh, newton_ymesh, x);
}

/*	an incredible recursive algorithm to solve a linear equation involving a trilinear square matrix AM = d
 *	algorithm found on wikipedia: https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm
 *	the middle diagonal of our matrix of interest is 2, so this value has been hard-coded for simplicity
 *	O(n) space complexity
 *	O(n) time complexity {incredible}
 *
 *	n = a natural number
 *	mu = the upper diagonal; an array of size n with n-2 populated indeces
 *	lambda = the lower diagonal; an array of size n with n-2 populated indeces
 *	d = the right-hand side of the linear equation; an array of size n-1 with n-2 populated indeces
 *	M = the solution to the linear system found by the algorithm; an array of size n with n-2 populated indeces
 */
void thomas(int n, precision* mu, precision* lambda, precision* d, precision* M)
{
	lambda[1] = lambda[1]/2;
	d[1] = d[1]/2;
	for(int i = 2; i < n-1; i++){lambda[i] = lambda[i]/(2-mu[i]*lambda[i-1]);}
	for(int i = 2; i < n; i++){d[i] = (d[i] - mu[i]*d[i-1])/(2 - mu[i]*lambda[i-1]);}
	M[n-1] = d[n-1];
	for(int i = n-2; i > 0; i--){M[i] = d[i]-lambda[i]*M[i+1];}
}

/*	computes the interpolating cubic splines with the given boundary conditions on a given x-y mesh evaluated at x
 *	O(n) space complexity
 *	O(nlog(n)) + O(log(n)) + O(n) time complexity {preprocessing; sort, search, thomas}
 *	O(1) time complexity {evaluation}
 *
 *	boundary = boolean flag; 0 for natural; 1 for first derivative hermite; 2 for second derivative hermite
 *	mesh_size = the sizes of the meshes of x and y values
 *	xmesh = mesh of x values
 *	ymesh = mesh of y values
 *	derivatives = an array of size 2 containing either [f'(a), f'(b)] or [f''(a), f''(b)] depending on the selected boundary conditions
 *	x = the place where we evaluate
 */
precision spline(int boundary, int mesh_size, precision* mesh, precision* values, precision* derivatives, precision x)
{
	int n = mesh_size - 1;
	sort(mesh_size, mesh, values);
	int index = search(mesh_size, mesh, x);
	if(index != n){index = index + 1;}
	precision d[n-1];
	precision lambda[n];
	precision mu[n];
	precision M[n+1];
	precision gamma[n];
	precision gamma_tilde[n];
	for(int i = 1; i < n; i++)
	{
		mu[i] = (mesh[i]-mesh[i-1])/(mesh[i+1]-mesh[i-1]);
		lambda[i] = (mesh[i+1]-mesh[i])/(mesh[i+1]-mesh[i-1]);
		d[i] = 6*((values[i+1]-values[i])/(mesh[i+1]-mesh[i])-(values[i]-values[i-1])/(mesh[i]-mesh[i-1]))/(mesh[i+1]-mesh[i-1]);
	}
	if(boundary == 0)//natural boundary conditions
	{
		M[0] = 0;
		M[n] = 0;
	} else if(boundary == 1)
	{//this is where i would set the first-order hermite boundary conditions... IF I HAD ANY
	} else {//second derivative hermite boundary conditions
		M[0] = derivatives[0];
		M[n] = derivatives[1];
		d[1] = d[1] - mu[1]*derivatives[0];
		d[n-1] = d[n-1] - lambda[n-1]*derivatives[1];
	}
	thomas(n, mu, lambda, d, M);
	for(int i = 1; i <= n; i++)
	{
		gamma[i-1] = (values[i] - values[i-1])/(mesh[i] - mesh[i-1]) - (mesh[i] - mesh[i-1])*(M[i] - M[i-1])/6;
		gamma_tilde[i-1] = values[i-1] - M[i-1]*pow(mesh[i] - mesh[i-1], 2)/6;
	}

	return M[index - 1]*pow(mesh[index] - x, 3)/(6*(mesh[index] - mesh[index-1]))
		+ M[index]*pow(x - mesh[index-1], 3)/(6*(mesh[index] - mesh[index-1]))
		+ gamma[index-1]*(x-mesh[index-1])
		+ gamma_tilde[index-1];
}

int main(int argc, char* argv[])
{
	int n;
	int num_eval;
	int choice;
	precision lower;
	precision upper;
	cout << "Enter the number of mesh points: ";
	cin >> n;
	cout << "Enter how many points you wish to evaluate: ";
	cin >> num_eval;
	precision x_mesh[n];
	precision y_mesh[n];
	precision eval_xmesh[num_eval];
	precision eval_ymesh[num_eval];
	std::ifstream x_file("3_x.txt");
	for(int i = 0; i < n; i++)
	{
		x_file >> x_mesh[i];
	}
	x_file.close();
	std::ifstream y_file("3_y.txt");
	for(int i = 0; i < n; i++)
	{
		y_file >> y_mesh[i];
	}
	y_file.close();
	std::ifstream eval_xfile("eval_x");
	for(int i = 0; i < num_eval; i++)
	{
		eval_xfile >> eval_xmesh[i];
	}
	eval_xfile.close();
	std::ifstream eval_yfile("eval_y");
	for(int i = 0; i < num_eval; i++)
	{
		eval_yfile >> eval_ymesh[i];
	}
	eval_yfile.close();
	//for(int i = 0; i < num_eval; i++)
	//{
		//eval_ymesh[i] = function1(1, eval_xmesh[i]);
	//}
	lower = x_mesh[0];
	upper = x_mesh[n-1];
	cout << "Enter 0 for newton, 1 for bernstein, 2 for piecewise, 3 for splines: ";
	cin >> choice;
	ofstream data;
	ofstream master;
	data.open("data");
	master.open("master");
	if(choice == 0)
	{
		for(int i = 0; i < num_eval; i++)
		{
			data << eval_xmesh[i] << " " << newton(n, x_mesh, y_mesh, eval_xmesh[i]) << endl;
			master << eval_xmesh[i] << " " << eval_ymesh[i] << endl;
		}
	} else if(choice == 1) {
		for(int i = 0; i < num_eval; i++)
		{
			data << eval_xmesh[i] << " " << bernstein(n, lower, upper, y_mesh, eval_ymesh[i]) << endl;
			master << eval_xmesh[i] << " " << eval_ymesh[i] << endl;
		}
	} else if(choice == 2) {
		int degree;
		cout << "Enter your desired degree of piecewise interpolation: ";
		cin >> degree;
		if((n-1) % degree != 0)
		{
			cout << "Your degree of interpolation is incompatible with the number of mesh points given to interpolate." << endl;
			return 0;
		}
		for(int i = 0; i < num_eval; i++)
		{
			data << eval_xmesh[i] << " " << piecewise(degree, n, x_mesh, y_mesh, eval_xmesh[i]) << endl;
			master << eval_xmesh[i] << " " << eval_ymesh[i] << endl;
		}
	} else if(choice == 3) {
		int boundary;
		cout << "Enter 0 for natural boundary conditions, 1 for 1st derivative hermite, 2 for 2nd derivative hermite: ";
		cin >> boundary;
		precision derivative[2] = {0, 0};
		if(boundary == 1)
		{
		} else if(boundary == 2) {
			cout << "Enter the second derivative at x = " << lower << " to interpolate: ";
			cin >> derivative[0];
			cout << "Enter the second derivative at x = " << upper << " to interpolate: ";
			cin >> derivative[1];
		}
		for(int i = 0; i < num_eval; i++)
		{
			data << eval_xmesh[i] << " " << spline(boundary, n, x_mesh, y_mesh, derivative, eval_xmesh[i]) << endl;;
			master << eval_xmesh[i] << " " << eval_ymesh[i] << endl;
		}
	} else {
		cout << "Invalid choice; please try again." << endl;
	}
	data.close();
	master.close();
	return 0;
}
