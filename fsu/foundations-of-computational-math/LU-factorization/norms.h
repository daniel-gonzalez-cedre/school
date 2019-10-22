//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif
precision norm_1(vector<precision> x);
precision norm_1(vector<vector<precision>> X);
precision norm_infinity(vector<precision> x);
precision norm_infinity(vector<vector<precision>> X);
precision norm_frobenius(vector<precision> x);
precision norm_frobenius(vector<vector<precision>> X);
