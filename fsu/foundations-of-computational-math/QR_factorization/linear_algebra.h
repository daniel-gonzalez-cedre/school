//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

vector<precision> scale(precision α, vector<precision> x);
vector<vector<precision>> scale(precision α, vector<vector<precision>> X);

vector<precision> sum(vector<precision> x, vector<precision> y);
vector<vector<precision>> sum(vector<vector<precision>> A, vector<vector<precision>> B);
vector<vector<precision>> dense_sum(vector<vector<precision>> A, vector<vector<precision>> B);

precision inner_product(vector<precision> x, vector<precision> y);
vector<vector<precision>> outer_product(vector<precision> x, vector<precision> y);

vector<precision> product(vector<vector<precision>> X, vector<precision> x);
vector<vector<precision>> product(vector<vector<precision>> A, vector<vector<precision>> B);
