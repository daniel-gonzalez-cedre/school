//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

void print_vector(vector<precision> v);
void print_matrix(vector<vector<precision>> A);

vector<precision> scale(precision α, vector<precision> x);
vector<vector<precision>> scale(precision α, vector<vector<precision>> X);

vector<vector<precision>> transpose(vector<vector<precision>> Q);

vector<precision> sum(vector<precision> x, vector<precision> y);
vector<precision> difference(vector<precision> x, vector<precision> y);
vector<vector<precision>> difference(vector<vector<precision>> X, vector<vector<precision>> Y);
vector<vector<precision>> sum(vector<vector<precision>> A, vector<vector<precision>> B);
vector<vector<precision>> dense_sum(vector<vector<precision>> A, vector<vector<precision>> B);

precision inner_product(vector<precision> x, vector<precision> y);
vector<vector<precision>> outer_product(vector<precision> x, vector<precision> y);

vector<precision> product(vector<vector<precision>> X, vector<precision> x);
vector<vector<precision>> product(vector<vector<precision>> A, vector<vector<precision>> B);
