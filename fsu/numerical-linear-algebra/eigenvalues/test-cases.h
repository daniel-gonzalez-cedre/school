//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

vector<vector<precision>> generate_toeplitz_tri(int dim);
vector<vector<precision>> gram_schmidt(int n);
vector<vector<precision>> eigenmatrix(int n);
