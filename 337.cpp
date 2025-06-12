#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Res {
    int noRoot;
    int withRoot;
};
class Solution {
   public:
    int rob(TreeNode* root) {
        Res res = f(root);
        return max(res.noRoot, res.withRoot);
    }
    Res f(TreeNode* root) {
        if (root == nullptr) return {0, 0};
        Res l = f(root->left);
        Res r = f(root->right);
        int noRoot = max(l.noRoot, l.withRoot) + max(r.noRoot, r.withRoot);
        int withRoot = root->val + l.noRoot + r.noRoot;
        return {noRoot, withRoot};
    }
};

int main() {
    string problemName = "337";
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
        auto res = sol.rob(root[0]);
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
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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