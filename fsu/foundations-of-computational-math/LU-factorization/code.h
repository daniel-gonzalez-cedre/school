//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

vector<vector<precision>> factor(vector<vector<precision>> A, int partial, int complete);
vector<precision> solve(vector<vector<precision>> LU, vector<precision> b);
