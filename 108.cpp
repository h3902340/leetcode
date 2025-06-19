#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return f(nums, 0, nums.size() - 1);
    }
    TreeNode* f(vector<int>& nums, int i, int j) {
        if (i > j) {
            return nullptr;
        }
        int mid = (i + j) >> 1;
        TreeNode* node = new TreeNode(nums[mid]);
        node->left = f(nums, i, mid - 1);
        node->right = f(nums, mid + 1, j);
        return node;
    }
};

int main() {
    string problemName = "108";
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
        auto nums = jread_vector(line_in);
        auto res = sol.sortedArrayToBST(nums);
        getline(file_out, line_out);
        auto ans = jread_binary_tree(line_out);
        printf("Case %d", ++caseCount);
        if (binaryTreeEqual(res, ans[0])) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(res, "res");
        jprint(ans[0], "ans");
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