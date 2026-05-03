#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 200;
const int M = 100;
int failure[M];
bool avail[N + M - 1];
void buildFailure(string &pattern)
{
    int m = pattern.size();
    failure[0] = 0;
    for (int i = 1; i < m; i++)
    {
        int j = failure[i - 1];
        while (true)
        {
            if (pattern[j] == pattern[i])
            {
                failure[i] = j + 1;
                break;
            }
            if (j == 0)
            {
                failure[i] = 0;
                break;
            }
            j = failure[j - 1];
        }
    }
}
bool KMP(string &s, string &pattern)
{
    int n = s.size();
    int m = pattern.size();
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        while (true)
        {
            if (s[i] == pattern[k])
            {
                k++;
                if (k == m)
                {
                    return true;
                }
                break;
            }
            if (k == 0)
            {
                break;
            }
            k = failure[k - 1];
        }
    }
    return false;
}

class Solution
{
public:
    bool rotateString(string s, string goal)
    {
        int n = s.size();
        int m = goal.size();
        if (n != m)
        {
            return false;
        }
        s += s;
        buildFailure(goal);
        return KMP(s, goal);
    }
};

int main()
{
    string problemName = "796";
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
        getline(file_in, line_in);
        auto goal = jread_string(line_in);
        auto res = sol.rotateString(s, goal);
        getline(file_out, line_out);
        auto ans = jread_bool(line_out);
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