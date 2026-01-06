#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e4;
TreeNode* lev[N];

class Solution {
   public:
    int maxLevelSum(TreeNode* root) {
        lev[0] = root;
        int f = 0;
        int b = 1;
        int mx = 0;
        int res = -1;
        int l = 1;
        while (f < b) {
            int bb = b;
            int s = 0;
            for (; f < bb; f++) {
                TreeNode* node = lev[f];
                s += node->val;
                if (node->left) {
                    lev[b++] = node->left;
                }
                if (node->right) {
                    lev[b++] = node->right;
                }
            }
            if (res == -1 || mx < s) {
                res = l;
                mx = s;
            }
            l++;
        }
        return res;
    }
};

int main() {
    string problemName = "1161";
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
        auto res = sol.maxLevelSum(root[0]);
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