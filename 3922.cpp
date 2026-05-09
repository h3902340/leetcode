#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution
{
public:
    int minFlips(string s)
    {
        int n = s.size();
        int one = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '1')
            {
                one++;
            }
        }
        if (one < 2)
        {
            return 0;
        }
        if (one == 2)
        {
            if (s[0] == '1' && s[n - 1] == '1')
            {
                return 0;
            }
            return 1;
        }
        int zero = n - one;
        if (s[0] == '1' && s[n - 1] == '1')
        {
            if (one - 2 < zero)
            {
                return one - 2;
            }
            return zero;
        }
        if (one - 1 < zero)
        {
            return one - 1;
        }
        return zero;
    }
};

int main()
{
    string problemName = "3922";
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
        auto s = jread_string(line_in);
        auto res = sol.minFlips(s);
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