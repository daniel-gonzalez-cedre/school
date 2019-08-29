//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif
vector<precision> generate_random_vector(int n);
vector<vector<precision>> generate_random_nonsingular(int n);
vector<vector<precision>> generate_upper_triangular(int n);
vector<vector<precision>> generate_lower_triangular(int n);
vector<vector<precision>> generate_unit_triangular(int n);
vector<vector<precision>> product(vector<vector<precision>> LU);
vector<vector<precision>> product(vector<vector<precision>> X, vector<vector<precision>> Y);
vector<precision> product(vector<vector<precision>> X, vector<precision> x);
vector<precision> permute_P(vector<precision> P, vector<precision> b);
vector<vector<precision>> permute_P(vector<precision> P, vector<vector<precision>> A);
vector<precision> permute_Q(vector<precision> Q, vector<precision> b);
vector<vector<precision>> permute_Q(vector<precision> Q, vector<vector<precision>> A);
precision solution_accuracy(vector<precision> x, vector<precision> tilde_x, precision (*norm)(vector<precision>));
precision factorization_accuracy(vector<vector<precision>> PAQ, vector<vector<precision>> LU, vector<vector<precision>> A, precision (*norm)(vector<vector<precision>>));
precision residual_accuracy(vector<precision> b, vector<vector<precision>> A, vector<precision> tilde_x, precision (*norm)(vector<precision>));
