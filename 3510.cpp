#include <vector>
#include <unordered_set>
#include <queue>
#include <set>
using namespace std;

// TODO: this code is unfinished, it has runtime error
struct SegmentTree
{
    long min;
    int minIndex;
};
struct Leaf
{
    long leftSum;
    long rightSum;
    int leftRange;
    int rightRange;
};
class Solution
{
public:
    int minimumPairRemoval(vector<int> &nums)
    {
        int n = nums.size();
        int size = 1;
        while (size < n)
        {
            size <<= 1;
        }
        int leafStart = size - 1;
        size = (size << 1) - 1;
        vector<SegmentTree> nodes(size);
        vector<Leaf> leaves(n - 1);
        int decreasingPair = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (nums[i] > nums[i + 1])
            {
                decreasingPair++;
            }
            nodes[leafStart + i] = {nums[i] + nums[i + 1], i};
            leaves[i] = {nums[i], nums[i + 1], 1, 1};
        }
        for (int i = n - 1; i < size; i++)
        {
            nodes[leafStart + i] = {INT64_MAX, i};
        }
        for (int i = leafStart - 1; i >= 0; i--)
        {
            SegmentTree left = nodes[(i << 1) + 1];
            SegmentTree right = nodes[(i << 1) + 2];
            int min = left.min;
            int minIndex = left.minIndex;
            if (min > right.min)
            {
                min = right.min;
                minIndex = right.minIndex;
            }
            nodes[i] = {min, minIndex};
        }
        int ans = 0;
        while (decreasingPair > 0)
        {
            SegmentTree node = nodes[0];
            Leaf leaf = leaves[node.minIndex];
            int leftIndex = node.minIndex - leaf.leftRange;
            if (leftIndex >= 0)
            {
                Leaf *left = &leaves[leftIndex];
                bool isDecreasingBefore = left->leftSum > left->rightSum;
                left->rightSum += leaf.rightSum;
                bool isDecreasingAfter = left->leftSum > left->rightSum;
                if (isDecreasingBefore)
                {
                    if (!isDecreasingAfter)
                    {
                        decreasingPair--;
                    }
                }
                else
                {
                    if (isDecreasingAfter)
                    {
                        decreasingPair++;
                    }
                }
                left->rightRange += leaf.rightRange;
                int c = leafStart + leftIndex;
                nodes[c].min = left->leftSum + left->rightSum;
            }
            int rightIndex = node.minIndex + leaf.rightRange;
            if (rightIndex < n - 1)
            {
                Leaf *right = &leaves[rightIndex];
                bool isDecreasingBefore = right->leftSum > right->rightSum;
                right->leftSum += leaf.leftSum;
                bool isDecreasingAfter = right->leftSum > right->rightSum;
                if (isDecreasingBefore)
                {
                    if (!isDecreasingAfter)
                    {
                        decreasingPair--;
                    }
                }
                else
                {
                    if (isDecreasingAfter)
                    {
                        decreasingPair++;
                    }
                }
                right->leftRange += leaf.leftRange;
                int c = leafStart + rightIndex;
                nodes[c].min = right->leftSum + right->rightSum;
                int p = (c - 1) >> 1;
                while (p >= 0)
                {
                    if (nodes[c].min < nodes[p].min)
                    {
                        nodes[p].min = nodes[c].min;
                        nodes[p].minIndex = nodes[c].minIndex;
                    }
                    else
                    {
                        break;
                    }
                    c = p;
                    p = (c - 1) >> 1;
                }
            }
            int c = leafStart + node.minIndex;
            nodes[c].min = INT64_MAX;
            int p = (c - 1) >> 1;
            while (p >= 0)
            {
                int minNode = (p << 1) + 1;
                if (nodes[minNode].min > nodes[minNode + 1].min)
                {
                    minNode++;
                }
                nodes[p].min = nodes[minNode].min;
                nodes[p].minIndex = nodes[minNode].minIndex;
                printf("p: %d, nodes[p].minIndex: %d, nodes[p].min: %ld\n", p, nodes[p].minIndex, nodes[p].min);
                p = (p - 1) >> 1;
            }
            if (leaf.leftSum > leaf.rightSum)
            {
                decreasingPair--;
            }
            if (leftIndex >= 0)
            {
                Leaf left = leaves[leftIndex];
                int c = leafStart + leftIndex;
                int p = (c - 1) >> 1;
                while (p >= 0)
                {
                    if (nodes[c].min < nodes[p].min)
                    {
                        nodes[p].min = nodes[c].min;
                        nodes[p].minIndex = nodes[c].minIndex;
                    }
                    else
                    {
                        break;
                    }
                    c = p;
                    p = (c - 1) >> 1;
                }
            }
            if (rightIndex < n - 1)
            {
                Leaf right = leaves[rightIndex];
                int c = leafStart + rightIndex;
                int p = (c - 1) >> 1;
                while (p >= 0)
                {
                    if (nodes[c].min < nodes[p].min)
                    {
                        nodes[p].min = nodes[c].min;
                        nodes[p].minIndex = nodes[c].minIndex;
                    }
                    else
                    {
                        break;
                    }
                    c = p;
                    p = (c - 1) >> 1;
                }
            }
            ans++;
            printf("{%ld,%ld}\n", leaf.leftSum, leaf.rightSum);
        }
        return ans;
    }
};

vector<int> nums = {2, 2, -1, 3, -2, 2, 1, 1, 1, 0, -1}; // 9
//  1. {2, 2, -1, 3, -2, 2, 1, 1, 1, 0, -1} // 5 {0, -1}
//  2. {2, 2, -1, 3, -2, 2, 1, 1, 1, -1} // 4 {-2, 2}
//  3. {2, 2, -1, 3, 0, 1, 1, 1, -1} // 3 {1,-1}
//  4. {2, 2, -1, 3, 0, 1, 1, 0} // 3 {2,-1}
//  5. {2, 1, 3, 0, 1, 1, 0} // 3 {0,1}
//  6. {2, 1, 3, 1, 1, 0} // 3 {1,0}
//  7. {2, 1, 3, 1, 1} // 2 {1,1}
//  8. {2, 1, 3, 2} // 2 {2,1}
//  9. {3, 3, 2} // 1 {3,2}
//  {3, 5}

// vector<int> nums = {5, 2, 3, 1}; // 2
// vector<int> nums = {3, 4, 1, 1, -3, 2, 4, 3}; // 5
// {3, 4, 1, 1, -3, 2, 4, 3}
// {3, 4, 1, -2, 2, 4, 3}
// {3, 4, -1, 2, 4, 3}
// {3, 4, 1, 4, 3}
int main()
{
    Solution sol;
    int ans = sol.minimumPairRemoval(nums);
    printf("ans = %d\n", ans);
    return 0;
}