#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define lg2(x) (31 - __builtin_clz(x))
class Solution {
   public:
    TreeNode* balanceBST(TreeNode* root) {
        auto head = TreeNode(0);
        head.right = root;
        int sz = treeToVine(&head);
        vineToTree(&head, sz);
        return head.right;
    }
    int treeToVine(TreeNode* root) {
        auto tail = root;
        auto rest = tail->right;
        int sz = 0;
        while (rest) {
            if (rest->left) {
                auto temp = rest->left;
                rest->left = temp->right;
                temp->right = rest;
                rest = temp;
                tail->right = temp;
            } else {
                tail = rest;
                rest = rest->right;
                sz++;
            }
        }
        return sz;
    }
    void vineToTree(TreeNode* root, int size) {
        auto leaves = size + 1 - (1 << lg2(size + 1));
        compress(root, leaves);
        size -= leaves;
        while (size > 1) {
            size >>= 1;
            compress(root, size);
        }
    }
    void compress(TreeNode* root, int count) {
        auto scanner = root;
        for (int i = 0; i < count; i++) {
            auto child = scanner->right;
            scanner->right = child->right;
            scanner = scanner->right;
            child->right = scanner->left;
            scanner->left = child;
        }
    }
};

int main() {
    string problemName = "1382";
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
        auto tree = jread_binary_tree(line_in);
        auto res = sol.balanceBST(tree[0]);
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