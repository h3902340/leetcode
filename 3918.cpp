#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1000;
int prime[N + 1];
bool isInit = false;
void init()
{
    memset(prime, 1, sizeof(prime));
    prime[0] = 0;
    prime[1] = 0;
    for (int i = 2; i <= N; i++)
    {
        if (prime[i] == 0)
        {
            prime[i] = prime[i - 1];
            continue;
        }
        for (int j = i * 2; j <= N; j += i)
        {
            prime[j] = 0;
        }
        prime[i] = prime[i - 1] + i;
    }
}
class Solution
{
public:
    int sumOfPrimesInRange(int n)
    {
        if (!isInit)
        {
            init();
            isInit = true;
        }
        int r = 0;
        int a = n;
        while (a > 0)
        {
            r = r * 10 + a % 10;
            a /= 10;
        }
        if (n < r)
        {
            swap(n, r);
        }
        return prime[n] - prime[r - 1];
    }
};

int main()
{
    string problemName = "3918";
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
        auto n = jread_int(line_in);
        auto res = sol.sumOfPrimesInRange(n);
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