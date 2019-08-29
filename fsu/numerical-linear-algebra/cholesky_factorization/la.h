using namespace std;

void print_vector(vector<double> x);
void print_matrix(vector<vector<double>> A);
vector<double> generate_spd_toeplitz(int n, int mod);
vector<vector<double>> full_toeplitz(vector<double> A);
vector<vector<double>> generate_spd_matrix(int n, int mod);
vector<vector<double>> transpose(vector<vector<double>> A);
vector<vector<double>> product(vector<vector<double>> A, vector<vector<double>> B);
bool equality(vector<vector<double>> A, vector<vector<double>> B);
