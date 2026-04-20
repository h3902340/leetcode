#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == p || root == q || root == nullptr) {
            return root;
        }
        auto l = lowestCommonAncestor(root->left, p, q);
        auto r = lowestCommonAncestor(root->right, p, q);
        if (l && r) {
            return root;
        }
        if (l) {
            return l;
        }
        if (r) {
            return r;
        }
        return nullptr;
    }
};

int main() {
    string problemName = "236";
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
        getline(file_in, line_in);
        auto pIdx = jread_int(line_in);
        getline(file_in, line_in);
        auto qIdx = jread_int(line_in);
        TreeNode* p;
        TreeNode* q;
        for (auto& e : root) {
            if (e == nullptr) {
                continue;
            }
            if (e->val == pIdx) {
                p = e;
            }
            if (e->val == qIdx) {
                q = e;
            }
        }
        auto res = sol.lowestCommonAncestor(root[0], p, q);
        getline(file_out, line_out);
        TreeNode* ans;
        auto ansIdx = jread_int(line_out);
        for (auto& e : root) {
            if (e == nullptr) {
                continue;
            }
            if (e->val == ansIdx) {
                ans = e;
                break;
            }
        }
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