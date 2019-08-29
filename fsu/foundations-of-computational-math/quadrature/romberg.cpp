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
const precision I4new = 4.1684*pow(10, -8);
const precision I5 = 6.3388758248682007492015186664523752790512027085370354;
const precision I6 = 0.386294361119890618834464242916353136151000268720510508241;

precision f1(precision x){return exp(x);}
precision f2(precision x){return exp(sin(2*x))*cos(2*x);}
precision f3(precision x){return tanh(x);}
precision f4(precision x){return x*cos(10*PI*x);}
precision f5(precision x){return x + 1/x;}
precision f6(precision x){return log(x);}

vector<precision> trapezoid(int n, precision a, precision b, precision delta, precision (*f)(precision), int itr)
{
	vector<precision> result;
	result.push_back(delta*(*f)(a)/2 + delta*(*f)(b)/2);
	for(int i = 1; i < n; i++){result[0] = result[0] + delta*(*f)(a + i*delta);}
	for(int i = 0; i < itr; i++)
	{
		n = n*2;
		delta = delta/2;
		result.push_back(result[i]/2);
		for(int j = 1; j < n; j = j + 2){result[i+1] = result[i+1] + delta*(*f)(a + j*delta);}
	}
	return result;
}

vector<precision> romberg(precision a, precision b, precision delta, precision (*f)(precision), int itr)
{
	vector<precision> t = trapezoid(1, a, b, delta, (*f), itr);
	vector<precision> T;//the upper diagonal of the Romberg pyramid
	T.push_back(t[0]);
	for(int i = 1; i <= itr; i++)
	{
		for(int j = 0; j < itr - i + 1; j++){t[j] = (pow(4, i)*t[j+1] - t[j])/(pow(4, i) - 1);}
		T.push_back(t[0]);
	}
	return T;
}

vector< vector<precision> > romberg_full(precision a, precision b, precision delta, precision (*f)(precision), int itr)
{
	vector<precision> t = trapezoid(1, a, b, delta, (*f), itr);
	vector< vector<precision> > T;//the full Romberg pyramid
	T.push_back(t);
	for(int i = 1; i <= itr; i++)
	{
		for(int j = 0; j < itr - i + 1; j++)
		{
			t[j] = (pow(4, i)*t[j+1] - t[j])/(pow(4, i) - 1);
		}
		t.pop_back();
		T.push_back(t);
	}
	return T;
}

int main(int argc, char* argv[])
{
	precision a = 0;
	precision b = PI/3;
	precision delta = (b-a);
	vector<precision> result1 = romberg(0, 3, 3, f1, 8);
	vector<precision> result2 = romberg(0, PI/3, PI/3, f2, 8);
	vector<precision> result3 = romberg(-2, 1, 3, f3, 16);
	vector<precision> result4 = romberg(0, 3.5, 3.5, f4, 16);
	vector<precision> result5 = romberg(0.1, 2.5, 2.4, f5, 16);
	vector<precision> result6 = romberg(1, 2, 1, f6, 16);
	vector< vector<precision> > result_full = romberg_full(0.1, 3.5, 3.5 - 0.1, f4, 10);
	ofstream data;
	data.open("data");
	//data.precision(numeric_limits<precision>::digits10);
	data.precision(numeric_limits<float>::digits10);
	vector<precision> temp = trapezoid(1, 0.1, 3.5, 3.5-0.1, f4, 10);
	for(int i = 0; i < result_full.size(); i++)
	{
		for(int j = 0; j < result_full[i].size(); j++)
		{
			data << abs(I4new - result_full[j][i]) << "\t";
		}
		data << endl;
	}
	for(int i = 0; i < temp.size(); i++)
	{
		data << I4new - temp[i] << endl;
	}
	data.close();
	return 0;
}
