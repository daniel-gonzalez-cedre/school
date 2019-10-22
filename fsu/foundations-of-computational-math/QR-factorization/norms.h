//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif
precision norm_L1(vector<precision> x);
precision norm_L1(vector<vector<precision>> X);
precision norm_L2(vector<precision> x);
precision norm_inf(vector<precision> x);
precision norm_inf(vector<vector<precision>> X);
precision norm_F(vector<precision> x);
precision norm_F(vector<vector<precision>> X);
