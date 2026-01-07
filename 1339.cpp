#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int MOD = 1e9 + 7;
class Solution {
   public:
    int maxProduct(TreeNode* root) { return g(root, f(root)) % MOD; }
    int f(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        root->val += f(root->left) + f(root->right);
        return root->val;
    }
    ll g(TreeNode* root, ll a) {
        if (root == nullptr) {
            return 0;
        }
        ll b = (a - root->val) * root->val;
        b = max(b, g(root->left, a));
        b = max(b, g(root->right, a));
        return b;
    }
};

int main() {
    string problemName = "1339";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    while (getline(file_in, line_in)) {
        auto root = jread_binary_tree(line_in);
        auto res = sol.maxProduct(root[0]);
        getline(file_out, line_out);
        auto ans = jread_int(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(res, "res");
        jprint(ans, "ans");
        printf("\n");
    }
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}