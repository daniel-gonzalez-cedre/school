/*
 * Daniel Gonzalez
 * Florida State University Dept. of Mathematics
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

//use the g++ directive -DSINGLE=1 at compile time to set precision from double (default) to single
#ifdef SINGLE 
typedef float precision;
#else
typedef double precision;
#endif

const precision PI = 3.141592653589793238462643383279502884197169399375105820974;
const precision I1 = 19.08553692318766774092852965458171789698790783855415014437;
const precision I2 = 0.688721337618082394122380379050022709663626871108323729493;
const precision I3 = -0.89122191687483724391125651192944945332781581115522281812;
const precision I4 = -0.050660591821168885721939731604863819452179387336123;
const precision I5 = 6.3388758248682007492015186664523752790512027085370354;
const precision I6 = 6.75;
const precision I7 = 0.386294361119890618834464242916353136151000268720510508241;

precision f1(precision x){return exp(x);}
precision f2(precision x){return exp(sin(2*x))*cos(2*x);}
precision f3(precision x){return tanh(x);}
precision f4(precision x){return x*cos(2*PI*x);}
precision f5(precision x){return x + 1/x;}
precision f6(precision x){return pow(x, 3) + pow(x, 2);}// min 2nd = -4;	max 2nd = 14;	min 4th = 0;	max 4th = 0 
precision f7(precision x){return log(x);}// min 2nd = -1;	max 2nd = -1/4;	min 4th = -6;	max 4th = -0.375

precision midpoint(int refine, int n, precision a, precision b, precision delta, precision (*f)(precision), precision analytic, precision error)
{
	precision result = 0;
	for(int i = 1; i < 2*n; i = i + 2){result = result + delta*(*f)((2*a + i*delta)/2);}
	while(refine && abs(result - analytic) > error)
	{
		n = n*3;
		delta = delta/3;
		result = result/3;
		for(int i = 1; i < 2*n; i = i + 2){if(i%3 != 0){result = result + delta*(*f)((2*a + i*delta)/2);}}
	}
	cout << "n = " << n << endl;
	return result;
}

precision open(int refine, int n, precision a, precision b, precision delta, precision (*f)(precision), precision analytic, precision error)
{
	precision result = 0;
	for(int i = 0; i < 3*n; i++){if(i%3 != 0){result = result + delta*(*f)(a + i*delta/3)/2;}}
	while(refine && abs(result - analytic) > error)
	{
		n = n*2;
		delta = delta/2;
		result = result/2;
		for(int i = 0; i < 3*n; i++){if(i%3 != 0 && i%2 != 0){result = result + delta*(*f)(a + i*delta/3)/2;}}
	}
	cout << "n = " << n << endl;
	return result;
}

precision trapezoid(int refine, int n, precision a, precision b, precision delta, precision (*f)(precision), precision analytic, precision error)
{
	precision result = delta*(*f)(a)/2 + delta*(*f)(b)/2;
	for(int i = 1; i < n; i++){result = result + delta*(*f)(a + i*delta);}
	while(refine && abs(result - analytic) > error)
	{
		n = n*2;
		delta = delta/2;
		result = result/2;
		for(int i = 1; i < n; i = i + 2){result = result + delta*(*f)(a + i*delta);}
	}
	cout << "n = " << n << endl;
	return result;
}

precision simpson(int refine, int n, precision a, precision b, precision delta, precision (*f)(precision), precision analytic, precision error)
{
	precision bounds = delta*((*f)(a) + (*f)(b))/6;
	precision middle = 0;
	for(int i = 1; i < 2*n; i = i + 2){middle = middle + 2*delta*(*f)(a + i*delta/2)/3;}
	for(int i = 1; i < n; i++){bounds = bounds + delta*(*f)(a + i*delta)/3;}
	while(refine && abs(bounds + middle - analytic) > error)
	{
		n = n*2;
		delta = delta/2;
		bounds = bounds/2 + middle/4;
		middle = 0;
		for(int i = 1; i < 2*n; i = i + 2){middle = middle + 2*delta*(*f)(a + i*delta/2)/3;}
	}
	cout << "n = " << n << endl;
	return bounds + middle;
}

precision gauss(int refine, int n, precision a, precision b, precision delta, precision (*f)(precision), precision analytic, precision error)
{
	precision z = sqrt(1.0/3);
	precision result = 0;
	for(int i = 1; i < 2*n; i = i + 2){result = result + delta*((*f)((2*a + i*delta + z*delta)/2) + (*f)((2*a + i*delta - z*delta)/2))/2;}
	while(refine && abs(result - analytic) > error)
	{
		n = n*2;
		delta = delta/2;
		result = 0;
		for(int i = 1; i < 2*n; i = i + 2){result = result + delta*((*f)((2*a + i*delta + z*delta)/2) + (*f)((2*a + i*delta - z*delta)/2))/2;}
	}
	cout << "n = " << n << endl;
	return result;
}

int main(int argc, char* argv[])
{
	int refine = 0;
	int n = 1;
	precision a = 0;
	precision b = 3;
	precision delta = (b-a)/n;
	precision error = 0.00001;
	vector<precision> mesh;
	for(precision i = a; i <= b; i = i + delta){mesh.push_back(i);}
	cout.precision(numeric_limits<precision>::digits10);
	cout << midpoint(refine, n, a, b, delta, f1, I1, error) << endl;
	return 0;
}
