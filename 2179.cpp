#include <vector>
using namespace std;
// TODO: Use Fenwick Tree
class Solution
{
public:
    long long goodTriplets(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        vector<int> nums2Indices(n);
        for (int i = 0; i < n; i++)
        {
            nums2Indices[nums2[i]] = i;
        }
        int d = 1;
        while (d < n)
        {
            d <<= 1;
        }
        vector<int> tree((d << 1) - 1, 0);
        long long ans = 0;
        for (int i = 0; i < n; i++)
        {
            int l = 0;
            int r = n - 1;
            int index = nums2Indices[nums1[i]];
            long long leftCount = 0;
            int j = 0;
            while (l < r)
            {
                int m = (l + r) >> 1;
                int leftSubtree = (j << 1) + 1;
                int rightSubtree = (j << 1) + 2;
                if (m < index)
                {
                    l = m + 1;
                    tree[rightSubtree]++;
                    leftCount += tree[leftSubtree];
                    j = rightSubtree;
                }
                else
                {
                    r = m;
                    tree[leftSubtree]++;
                    j = leftSubtree;
                }
            }
            ans += leftCount * (n - 1 - index - (i - leftCount));
        }
        return ans;
    }
};

vector<int> nums1 = {2, 0, 1, 3};
vector<int> nums2 = {0, 1, 2, 3};

int main()
{
    Solution sol;
    long long ans = sol.goodTriplets(nums1, nums2);
    printf("ans = %lld\n", ans); // 1
    return 0;
}