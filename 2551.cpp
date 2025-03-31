#include <vector>
using namespace std;

class Solution
{
private:
    void kth_element(vector<int> &nums, int i, int j, int k, int debug)
    {
        srand(time(NULL));
        int l = i + 1;
        int r = j;
        int mid = rand() % (j - i + 1) + i;
        int p = nums[mid];
        nums[mid] = nums[i];
        while (true)
        {
            while (l <= r)
            {
                if (nums[l] > p)
                {
                    int temp = nums[l];
                    nums[l] = nums[r];
                    nums[r] = temp;
                    --r;
                }
                else
                {
                    ++l;
                }
            }
            nums[i] = nums[r];
            nums[r] = p;
            if (r == k)
                break;
            if (r < k)
            {
                i = r + 1;
            }
            else
            {
                j = r - 1;
            }
            l = i + 1;
            r = j;
            mid = rand() % (j - i + 1) + i;
            p = nums[mid];
            nums[mid] = nums[i];
        }
    }

public:
    long long putMarbles(vector<int> &weights, int k)
    {
        int n = weights.size();
        if (k == 1 || k == n)
            return 0;
        for (int i = 0; i < n - 1; ++i)
        {
            weights[i] += weights[i + 1];
        }
        weights.pop_back();
        --n;
        long long ans = 0;
        int j = n - 1;
        --k;
        if (k > n >> 1)
        {
            k = n - k;
        }
        kth_element(weights, 0, n - 1, k - 1, 0);
        kth_element(weights, k, n - 1, n - k, 1);
        for (int i = 0; i < k; ++i)
        {
            ans += weights[j--] - weights[i];
        }
        return ans;
    }
};

vector<int> weights = {56, 41, 27, 71, 62, 57, 67, 34, 8, 71, 2, 12, 52, 1, 64, 43, 32, 42, 9, 25, 73, 29, 31};
int k = 5;

int main()
{
    Solution sol;
    long long ans = sol.putMarbles(weights, k);
    printf("ans = %lld\n", ans); // 342
    return 0;
}