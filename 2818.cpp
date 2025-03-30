#include <vector>
#include <iostream>
using namespace std;

bool done = false;
const int PRIME_SCORE_SIZE = 100001;
vector<int> primeScore(PRIME_SCORE_SIZE, 0);

struct NumInfo
{
    int value;
    int primeFactor;
    int left;
    int right;
};
class Solution
{
private:
    int powModulo(int a, int b, int m)
    {
        if (b == 0)
            return 1;
        if (b & 1)
        {
            long temp = powModulo(a, b - 1, m);
            return (a * temp) % m;
        }
        long temp = powModulo(a, b >> 1, m);
        return (temp * temp) % m;
    }

    const int BUCKET_SIZE_2 = 512;
    const int MASK_2 = 511;
    void radixSortByNum(vector<NumInfo> &nums)
    {
        int n = nums.size();
        vector<int> buckets(BUCKET_SIZE_2);
        vector<NumInfo> temp(n);
        for (int j = 0; j < 18; j += 9)
        {
            for (auto &e : nums)
            {
                buckets[(e.value >> j) & MASK_2]++;
            }
            for (int i = 1; i < BUCKET_SIZE_2; i++)
            {
                buckets[i] += buckets[i - 1];
            }
            for (int i = n - 1; i >= 0; i--)
            {
                temp[--buckets[(nums[i].value >> j) & MASK_2]] = nums[i];
            }
            fill(buckets.begin(), buckets.end(), 0);
            nums.swap(temp);
        }
    }

public:
    Solution()
    {
        if (done)
            return;
        for (int i = 2; i < PRIME_SCORE_SIZE; i++)
        {
            if (primeScore[i] == 0)
            {
                for (int j = i; j < PRIME_SCORE_SIZE; j += i)
                {
                    primeScore[j]++;
                }
            }
        }
        done = true;
    }
    int maximumScore(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<NumInfo> numInfos(n);
        for (int i = 0; i < n; i++)
        {
            numInfos[i].value = nums[i];
            numInfos[i].primeFactor = primeScore[nums[i]];
        }
        stack<int> stack;
        stack.push(0);
        numInfos[0].left = 1;
        for (int i = 1; i < n; i++)
        {
            int right = 1;
            while (!stack.empty() && numInfos[stack.top()].primeFactor < numInfos[i].primeFactor)
            {
                numInfos[stack.top()].right = right;
                right += numInfos[stack.top()].left;
                stack.pop();
            }
            stack.push(i);
            numInfos[i].left = right;
        }
        int right = 1;
        while (!stack.empty())
        {
            numInfos[stack.top()].right = right;
            right += numInfos[stack.top()].left;
            stack.pop();
        }
        radixSortByNum(numInfos);
        long ans = 1;
        int i = n - 1;
        const int divider = 1000000007;
        while (k > 0 && i >= 0)
        {
            long subArrayCount = (long)numInfos[i].left * numInfos[i].right;
            while (i > 0 && numInfos[i].value == numInfos[i - 1].value)
            {
                i--;
                subArrayCount += (long)numInfos[i].left * numInfos[i].right;
            }
            if (k < subArrayCount)
            {
                ans *= powModulo(numInfos[i].value, k, divider);
                k = 0;
            }
            else
            {
                ans *= powModulo(numInfos[i].value, subArrayCount, divider);
                k -= subArrayCount;
            }
            ans %= divider;
            i--;
        }
        return ans;
    }
};

vector<int> nums = {19, 12, 14, 6, 10, 18};
int k = 3;

int main()
{
    Solution sol = Solution();
    int ans = sol.maximumScore(nums, k);
    printf("ans = %d\n", ans); // 4788
    return 0;
}