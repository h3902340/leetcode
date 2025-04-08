#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;
struct Node
{
    Node *left;
    Node *right;
    int leftIndex;
    int rightIndex;
    int leftRange;
    int rightRange;
    long leftSum;
    long rightSum;
    long sum;
    Node() : left(nullptr), right(nullptr), leftIndex(-1), rightIndex(-1), leftRange(0), rightRange(0), leftSum(0), rightSum(0), sum(0) {}
};
struct nodeGreater
{
    bool operator()(const Node &a, const Node &b) const
    {
        if (a.sum == b.sum)
        {
            return a.leftIndex > b.leftIndex;
        }
        return a.sum > b.sum;
    }
};
class Solution
{
public:
    int minimumPairRemoval(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return 0;
        if (n == 2)
            return nums[0] > nums[1];
        int ans = 0;
        int decreasingPair = 0;
        vector<Node> nodes(n - 1);
        for (int i = 0; i < n - 1; i++)
        {
            int l = nums[i];
            int r = nums[i + 1];
            decreasingPair += l > r;
            nodes[i].leftIndex = i;
            nodes[i].rightIndex = i + 1;
            nodes[i].leftRange = 1;
            nodes[i].rightRange = 1;
            nodes[i].leftSum = l;
            nodes[i].rightSum = r;
            nodes[i].sum = l + r;
            nums[i] = 1;
        }
        nums[n - 1] = 1;
        nodes[0].right = &nodes[1];
        for (int i = 1; i < n - 2; i++)
        {
            nodes[i].right = &nodes[i + 1];
            nodes[i].left = &nodes[i - 1];
        }
        nodes[n - 2].left = &nodes[n - 3];
        vector<Node> heap((n - 1) << 1);
        for (int i = 0; i < n - 1; i++)
        {
            heap[i] = nodes[i];
        }
        int heapSize = n - 1;
        make_heap(heap.begin(), heap.begin() + heapSize, nodeGreater());
        while (decreasingPair > 0)
        {
            Node f = heap.front();
            pop_heap(heap.begin(), heap.begin() + heapSize, nodeGreater());
            heapSize--;
            int l_new = nums[f.leftIndex];
            int r_new = nums[f.rightIndex];
            if (l_new == f.leftRange && r_new == f.rightRange)
            {
                if (f.left)
                {
                    Node *leftNode = f.left;
                    if (leftNode->leftSum > f.leftSum)
                    {
                        if (leftNode->leftSum <= f.sum)
                        {
                            decreasingPair--;
                        }
                    }
                    else
                    {
                        if (leftNode->leftSum > f.sum)
                        {
                            decreasingPair++;
                        }
                    }
                    leftNode->rightRange += f.rightRange;
                    nums[leftNode->rightIndex] = leftNode->rightRange;
                    leftNode->right = f.right;
                    leftNode->rightSum = f.sum;
                    leftNode->sum = leftNode->leftSum + leftNode->rightSum;
                    heap[heapSize] = *leftNode;
                    heapSize++;
                    push_heap(heap.begin(), heap.begin() + heapSize, nodeGreater());
                }
                if (f.right)
                {
                    Node *rightNode = f.right;
                    if (rightNode->rightSum < f.rightSum)
                    {
                        if (rightNode->rightSum >= f.sum)
                        {
                            decreasingPair--;
                        }
                    }
                    else
                    {
                        if (rightNode->rightSum < f.sum)
                        {
                            decreasingPair++;
                        }
                    }
                    rightNode->leftRange += f.leftRange;
                    nums[rightNode->leftIndex] = rightNode->leftRange;
                    rightNode->left = f.left;
                    rightNode->leftSum = f.sum;
                    rightNode->sum = rightNode->leftSum + rightNode->rightSum;
                    heap[heapSize] = *rightNode;
                    heapSize++;
                    push_heap(heap.begin(), heap.begin() + heapSize, nodeGreater());
                }
                if (f.leftSum > f.rightSum)
                {
                    decreasingPair--;
                }
                ans++;
            }
        }
        return ans;
    }
};

vector<int> nums = {2, 2, -1, 3, -2, 2, 1, 1, 1, 0, -1};
// 1. {2, 2, -1, 3, -2, 2, 1, 1, 1, 0, -1} // 5 {0, -1}
// 2. {2, 2, -1, 3, -2, 2, 1, 1, 1, -1} // 4 {-2, 2}
// 3. {2, 2, -1, 3, 0, 1, 1, 1, -1} // 3 {1,-1}
// 4. {2, 2, -1, 3, 0, 1, 1, 0} // 3 {2,-1}
// 5. {2, 1, 3, 0, 1, 1, 0} // 3 {0,1}
// 6. {2, 1, 3, 1, 1, 0} // 3 {1,0}
// 7. {2, 1, 3, 1, 1} // 2 {1,1}
// 8. {2, 1, 3, 2} // 2 {2,1}
// 9. {3, 3, 2} // 1 {3,2}
// {3, 5}
int main()
{
    Solution sol;
    int ans = sol.minimumPairRemoval(nums);
    printf("ans = %d\n", ans); // 9
    return 0;
}