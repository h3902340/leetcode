#include <fstream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

int jread_int(string line);
double jread_double(string line);
long jread_long(string line);
long long jread_longlong(string line);
char jread_char(string line);
string jread_string(string line);
vector<int> jread_vector(string line);
vector<double> jread_vector_double(string line);
vector<char> jread_vector_char(string line);
vector<vector<int>> jread_vector2d(string line);
vector<vector<char>> jread_vector2d_char(string line);
vector<string> jread_vector_string(string line);
vector<vector<string>> jread_vector2d_string(string line);
ListNode* jread_list(string line);
vector<ListNode*> jread_vector_list(string line);
vector<TreeNode*> jread_binary_tree(string line);

void jprint_int(int num, string name);
void jprint_double(double num, string name);
void jprint_long(long num, string name);
void jprint_longlong(long long num, string name);
void jprint_char(char c, string name);
void jprint_string(string s, string name);
void jprint_list(ListNode* vec, string name);
void jprint_vector(vector<int> vec, string name);
void jprint_vector_double(vector<double> vec, string name);
void jprint_vector_char(vector<char> vec, string name);
void jprint_vector2d(vector<vector<int>> vec, string name);
void jprint_vector2d_char(vector<vector<char>> vec, string name);
void jprint_vector_string(vector<string> vec, string name);
void jprint_vector2d_string(vector<vector<string>> vec, string name);
void jprint_vector_size(vector<int> vec, string name);
void jprint_vector2d_size(vector<vector<int>> vec, string name);
void jprint_array(int vec[], int n, string name);
void jprint_array_char(char vec[], int n, string name);
void jprint_binary_tree(TreeNode* root, string name);

chrono::steady_clock::time_point jtimer();
void jprint_time(chrono::steady_clock::time_point begin,
                 chrono::steady_clock::time_point end);

bool anyOrderEqual(vector<int> a, vector<int> b);
bool listEqual(ListNode* a, ListNode* b);