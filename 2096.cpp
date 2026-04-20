#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        int res1 = 0;
        string res2 = "";
        f(root, startValue, destValue, res1, res2);
        int n = res2.size();
        string res(res1 + n, 'U');
        for (int i = 0; i < n; i++) {
            res[res1 + n - 1 - i] = res2[i];
        }
        return res;
    }
    int f(TreeNode* root, int s, int t, int& res1, string& res2) {
        if (root == nullptr) {
            return 0;
        }
        int a = f(root->left, s, t, res1, res2);
        int b = f(root->right, s, t, res1, res2);
        if (a == 3 || b == 3) {
            return 3;
        }
        if (a & 1) {
            res1++;
        }
        if (a & 2) {
            res2 += 'L';
        }
        if (b & 1) {
            res1++;
        }
        if (b & 2) {
            res2 += 'R';
        }
        int c = a | b;
        if (root->val == s) {
            c |= 1;
        }
        if (root->val == t) {
            c |= 2;
        }
        return c;
    }
};

int main() {
    string problemName = "2096";
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
        auto root = jread_binary_tree(line_in)[0];
        getline(file_in, line_in);
        auto startValue = jread_int(line_in);
        getline(file_in, line_in);
        auto destValue = jread_int(line_in);
        auto res = sol.getDirections(root, startValue, destValue);
        getline(file_out, line_out);
        auto ans = jread_string(line_out);
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