#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    TreeNode* node;
    int depth;
};
const int N = 1e4;
Data q[N];

class Solution {
   public:
    int maxDepth(TreeNode* root) {
        int l = 0;
        int r = 0;
        q[r++] = {root, 1};
        int res = 0;
        while (l < r) {
            Data& f = q[l++];
            if (f.node == nullptr) continue;
            res = f.depth;
            if (f.node->left) {
                q[r++] = {f.node->left, f.depth + 1};
            }
            if (f.node->right) {
                q[r++] = {f.node->right, f.depth + 1};
            }
        }
        return res;
    }
};

int main() {
    string problemName = "104";
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
        auto res = sol.maxDepth(root[0]);
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