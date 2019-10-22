//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

vector<precision> scale(precision α, vector<precision> x);
vector<vector<precision>> scale(precision α, vector<vector<precision>> X);
precision inner_product(vector<precision> x, vector<precision> y);
vector<vector<precision>> outer_product(vector<precision> x, vector<precision> y);
vector<precision> product(vector<vector<precision>> A, vector<precision> x);
vector<vector<precision>> inverse2x2(vector<vector<precision>> J);
vector<precision> sum(vector<precision> x, vector<precision> y);
vector<vector<precision>> sum(vector<vector<precision>> X, vector<vector<precision>> Y);
vector<precision> difference(vector<precision> x, vector<precision> y);
vector<vector<precision>> difference(vector<vector<precision>> X, vector<vector<precision>> Y);
