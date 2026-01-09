#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 500;
int d[N];

class Solution {
   public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        f(root);
        return g(root);
    }
    int f(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        d[root->val] = 1 + max(f(root->left), f(root->right));
        return d[root->val];
    }
    TreeNode* g(TreeNode* root) {
        int l = root->left ? d[root->left->val] : 0;
        int r = root->right ? d[root->right->val] : 0;
        if (l == r) {
            return root;
        }
        if (l < r) {
            return g(root->right);
        }
        return g(root->left);
    }
};

int main() {
    string problemName = "865";
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
        auto res = sol.subtreeWithAllDeepest(root[0]);
        getline(file_out, line_out);
        auto ans = jread_binary_tree(line_out)[0];
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