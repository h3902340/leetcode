#include <fstream>
#include <vector>
#include <chrono>
using namespace std;

class Node {
   public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

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
vector<Node*> jread_graph(string line);

void jprint(int num, string name);
void jprint(double num, string name);
void jprint(long num, string name);
void jprint(long long num, string name);
void jprint(char c, string name);
void jprint(string s, string name);
void jprint(ListNode* vec, string name);
void jprint(vector<int> vec, string name);
void jprint(vector<long long> vec, string name);
void jprint(vector<double> vec, string name);
void jprint(vector<char> vec, string name);
void jprint(vector<vector<int>> vec, string name);
void jprint(vector<vector<char>> vec, string name);
void jprint(vector<string> vec, string name);
void jprint(vector<vector<string>> vec, string name);
void jprint_vector_size(vector<int> vec, string name);
void jprint_vector2d_size(vector<vector<int>> vec, string name);
void jprint(bool vec[], int n, string name);
void jprint(int vec[], int n, string name);
void jprint(long long vec[], int n, string name);
void jprint(char vec[], int n, string name);
void jprint(TreeNode* root, string name);
void jprint(Node* root, string name);

chrono::steady_clock::time_point jtimer();
void jprint_time(chrono::steady_clock::time_point begin,
                 chrono::steady_clock::time_point end);
void jprint_time(chrono::steady_clock::time_point begin,
                 chrono::steady_clock::time_point end, string name);

bool anyOrderEqual(vector<int> a, vector<int> b);
bool anyOrderEqual(vector<vector<int>> a, vector<vector<int>> b);
bool coorEqual(vector<vector<int>> a, vector<vector<int>> b);
bool anyOrderEqual(vector<string> a, vector<string> b);
bool anyOrderEqual(vector<vector<string>> a, vector<vector<string>> b);
bool listEqual(ListNode* a, ListNode* b);
bool graphEqual(Node* a, Node* b);
bool binaryTreeEqual(TreeNode* a, TreeNode* b);