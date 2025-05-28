#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 500;
vector<int> adj[NMAX];
TreeNode* q[NMAX];
int depth[NMAX];
int parent[NMAX];
int q2[NMAX];

class Solution {
   public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        for (int i = 0; i < NMAX; i++) {
            adj[i].clear();
        }
        int l = 0;
        int r = 0;
        q[r++] = root;
        int targetIndex = -1;
        while (l < r) {
            TreeNode* t = q[l];
            if (t == target) {
                targetIndex = l;
            }
            if (t->right) {
                adj[l].push_back(r);
                adj[r].push_back(l);
                q[r] = t->right;
                r++;
            }
            if (t->left) {
                adj[l].push_back(r);
                adj[r].push_back(l);
                q[r] = t->left;
                r++;
            }
            l++;
        }
        vector<int> res;
        l = 0;
        r = 1;
        q2[l] = targetIndex;
        depth[targetIndex] = 0;
        parent[targetIndex] = -1;
        while (l < r) {
            int f = q2[l++];
            if (depth[f] == k) {
                res.push_back(q[f]->val);
                continue;
            }
            if (depth[f] > k) break;
            for (auto& e : adj[f]) {
                if (e == parent[f]) continue;
                q2[r++] = e;
                depth[e] = depth[f] + 1;
                parent[e] = f;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "863";
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
        auto root = tree[0];
        getline(file_in, line_in);
        int targetVal = jread_int(line_in);
        TreeNode* target = nullptr;
        for (int i = 0; i < tree.size(); i++) {
            if (tree[i]->val == targetVal) {
                target = tree[i];
                break;
            }
        }
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.distanceK(root, target, k);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
        printf("Case %d", ++caseCount);
        if (anyOrderEqual(res, ans)) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_binary_tree(root, "root");
        jprint_vector(res, "res");
        jprint_vector(ans, "ans");
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