#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int arr[N];
int lengthOfLIS(int n)
{
    if (n == 0)
    {
        return 0;
    }
    int i = 0;
    for (int j = 1; j < n; j++)
    {
        if (arr[i] <= arr[j])
        {
            i++;
            arr[i] = arr[j];
        }
        else if (arr[i] > arr[j])
        {
            int l = 0;
            int r = i;
            int max = -1;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (arr[mid] > arr[j])
                {
                    r = mid - 1;
                }
                else
                {
                    max = mid;
                    l = mid + 1;
                }
            }
            arr[max + 1] = arr[j];
        }
    }
    return i + 1;
}
vector<int> mp[N + 1];
class Solution
{
public:
    int maxFixedPoints(vector<int> &nums)
    {
        int n = nums.size();
        int mx = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] <= i)
            {
                mp[nums[i]].push_back(i - nums[i]);
            }
            mx = max(mx, nums[i]);
        }
        int k = 0;
        for (int i = 0; i <= mx; i++)
        {
            for (int j = mp[i].size() - 1; j >= 0; j--)
            {
                arr[k++] = mp[i][j];
            }
            mp[i].clear();
        }
        return lengthOfLIS(k);
    }
};

int main()
{
    string problemName = "3920";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    while (getline(file_in, line_in))
    {
        auto nums = jread_vector(line_in);
        auto res = sol.maxFixedPoints(nums);
        getline(file_out, line_out);
        auto ans = jread_int(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans)
        {
            passCount++;
            printf(" %s(PASS)", KGRN);
        }
        else
        {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(res, "res");
        jprint(ans, "ans");
        printf("\n");
    }
    if (allPass)
    {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    }
    else
    {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}