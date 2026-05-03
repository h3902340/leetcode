#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1e5;
ll pre[N];
ll suf[N];
class Solution
{
public:
    vector<int> minCost(vector<int> &nums, vector<vector<int>> &queries)
    {
        int n = nums.size();
        int q = queries.size();
        pre[0] = 0;
        pre[1] = 1;
        for (int i = 1; i < n - 1; i++)
        {
            int a = abs(nums[i] - nums[i - 1]);
            int b = abs(nums[i] - nums[i + 1]);
            if (a <= b)
            {
                pre[i + 1] = pre[i] + b;
            }
            else
            {
                pre[i + 1] = pre[i] + 1;
            }
        }
        suf[n - 1] = 0;
        suf[n - 2] = 1;
        for (int i = n - 2; i > 0; i--)
        {
            int a = abs(nums[i] - nums[i - 1]);
            int b = abs(nums[i] - nums[i + 1]);
            if (a > b)
            {
                suf[i - 1] = suf[i] + a;
            }
            else
            {
                suf[i - 1] = suf[i] + 1;
            }
        }
        vector<int> res(q);
        for (int i = 0; i < q; i++)
        {
            int l = queries[i][0];
            int r = queries[i][1];
            if (l < r)
            {
                res[i] = pre[r] - pre[l];
            }
            else
            {
                res[i] = suf[r] - suf[l];
            }
        }
        return res;
    }
};

int main()
{
    string problemName = "3919";
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
        getline(file_in, line_in);
        auto queries = jread_vector2d(line_in);
        auto res = sol.minCost(nums, queries);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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