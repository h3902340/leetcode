#include <utility>
#include <_printf.h>
#include <stack>
#include <queue>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    TreeNode *lcaDeepestLeaves(TreeNode *root)
    {
        pair<int, TreeNode *> ans = lcaDeepestLeavesRecursive(root);
        return ans.second;
    }

private:
    pair<int, TreeNode *> lcaDeepestLeavesRecursive(TreeNode *root)
    {
        if (!root)
        {
            return {0, nullptr};
        }
        pair<int, TreeNode *> d1 = lcaDeepestLeavesRecursive(root->left);
        pair<int, TreeNode *> d2 = lcaDeepestLeavesRecursive(root->right);
        if (d1.first == d2.first)
        {
            return {d1.first + 1, root};
        }
        else if (d1 > d2)
        {
            return {d1.first + 1, d1.second};
        }
        else
        {
            return {d2.first + 1, d2.second};
        }
    }
};

const int arrLen = 9;
int nodes[arrLen]{1, 2, -1, 3, 4, -1, 6, -1, 5};

int main()
{
    TreeNode *treeNodes[arrLen];
    int curr = 1;
    int next = 1;
    treeNodes[0] = new TreeNode(nodes[0]);
    for (int i = 0; i < arrLen; i++)
    {
        if (i == curr)
        {
            curr = next;
        }
        TreeNode *node = treeNodes[i];
        if (!node)
        {
            continue;
        }
        if (next >= arrLen || nodes[next] == -1)
        {
            node->left = nullptr;
        }
        else
        {
            node->left = new TreeNode(nodes[next]);
        }
        if (next < arrLen)
        {
            treeNodes[next] = node->left;
        }
        next++;
        if (next >= arrLen || nodes[next] == -1)
        {
            node->right = nullptr;
        }
        else
        {
            node->right = new TreeNode(nodes[next]);
        }
        if (next < arrLen)
        {
            treeNodes[next] = node->right;
        }
        next++;
    }
    Solution sol;
    TreeNode *lca = sol.lcaDeepestLeaves(treeNodes[0]);
    printf("lca = [%d", lca->val);
    queue<TreeNode *> queue;
    queue.push(lca->left);
    queue.push(lca->right);
    int i = (lca->left != nullptr) + (lca->right != nullptr);
    while (!queue.empty() && i > 0)
    {
        TreeNode *f = queue.front();
        queue.pop();
        if (f)
        {
            i--;
            printf(",%d", f->val);
            queue.push(f->left);
            queue.push(f->right);
            i += (f->left != nullptr);
            i += (f->right != nullptr);
        }
        else
        {
            printf(",null");
        }
    }
    printf("]\n");
    return 0;
}