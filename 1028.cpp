#include <string>
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
    TreeNode *recoverFromPreorder(string traversal)
    {
        stack<TreeNode *> waitingStack;
        int depth = 0;
        int val = 0;
        int i = 0;
        while (i < traversal.length())
        {
            while (traversal[i] == '-')
            {
                depth++;
                i++;
            }
            while (isdigit(traversal[i]))
            {
                val = val * 10 + (traversal[i] - '0');
                i++;
            }
            TreeNode *node = new TreeNode();
            node->val = val;
            while (waitingStack.size() != depth)
            {
                waitingStack.pop();
            }
            if (!waitingStack.empty())
            {
                if (waitingStack.top()->left)
                {
                    waitingStack.top()->right = node;
                }
                else
                {
                    waitingStack.top()->left = node;
                }
            }
            waitingStack.push(node);
            depth = 0;
            val = 0;
        }
        while (waitingStack.size() != 1)
        {
            waitingStack.pop();
        }
        return waitingStack.top();
    }
};

string traversal = "1-401--349---90--88";

int main()
{
    Solution sol;
    TreeNode *root = sol.recoverFromPreorder(traversal);
    vector<int> nodes;
    queue<TreeNode *> queue;
    queue.push(root);
    while (!queue.empty())
    {
        TreeNode *node = queue.front();
        queue.pop();
        if (node)
        {
            nodes.push_back(node->val);
            queue.push(node->left);
            queue.push(node->right);
        }
        else
        {
            nodes.push_back(-1);
        }
    }
    int lastNodeVal = nodes[nodes.size() - 1];
    while (lastNodeVal == -1)
    {
        nodes.pop_back();
        lastNodeVal = nodes[nodes.size() - 1];
    }
    printf("[");
    for (int i = 0; i < nodes.size() - 1; i++)
    {
        printf("%d,", nodes[i]);
    }
    printf("%d", nodes[nodes.size() - 1]);
    printf("]\n");

    return 0;
}