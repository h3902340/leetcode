#include <fstream>
using namespace std;

int jread_int(string line);
long jread_long(string line);
long long jread_longlong(string line);
string jread_string(string line);
vector<int> jread_vector(string line);
vector<vector<int>> jread_vector2d(string line);

void jprint_int(int num, string name);
void jprint_long(long num, string name);
void jprint_longlong(long long num, string name);
void jprint_string(string s, string name);
void jprint_vector(vector<int> vec, string name);
void jprint_vector2d(vector<vector<int>> vec, string name);
void jprint_vector_size(vector<int> vec, string name);
void jprint_vector2d_size(vector<vector<int>> vec, string name);
void jprint_array(int vec[], int n, string name);

chrono::steady_clock::time_point jtimer();
void jprint_time(chrono::steady_clock::time_point begin,
                 chrono::steady_clock::time_point end);