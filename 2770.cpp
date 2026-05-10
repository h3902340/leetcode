#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1000;
int dp[N];
class Solution
{
public:
    int maximumJumps(vector<int> &nums, int target)
    {
        int n = nums.size();
        dp[0] = 0;
        for (int j = 1; j < n; j++)
        {
            dp[j] = -1;
            for (int i = 0; i < j; i++)
            {
                if (abs(nums[j] - nums[i]) <= target && dp[i] != -1)
                {
                    dp[j] = max(dp[j], dp[i] + 1);
                }
            }
        }
        return dp[n - 1];
    }
};

int main()
{
    string problemName = "2770";
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
        int target = jread_int(line_in);
        auto res = sol.maximumJumps(nums, target);
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