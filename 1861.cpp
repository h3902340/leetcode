#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution
{
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>> &boxGrid)
    {
        int m = boxGrid.size();
        int n = boxGrid[0].size();
        vector<vector<char>> res(n, vector<char>(m));
        for (int i = 0; i < m; i++)
        {
            int b = n - 1;
            for (int j = n - 1; j >= 0; j--)
            {
                if (boxGrid[i][j] == '.')
                {
                    continue;
                }
                if (boxGrid[i][j] == '*')
                {
                    for (int k = b; k > j; k--)
                    {
                        res[k][m - 1 - i] = '.';
                    }
                    res[j][m - 1 - i] = '*';
                    b = j - 1;
                    continue;
                }
                res[b--][m - 1 - i] = '#';
            }
            for (int k = b; k >= 0; k--)
            {
                res[k][m - 1 - i] = '.';
            }
        }
        return res;
    }
};

int main()
{
    string problemName = "1861";
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
        auto boxGrid = jread_vector2d_char(line_in);
        auto res = sol.rotateTheBox(boxGrid);
        getline(file_out, line_out);
        auto ans = jread_vector2d_char(line_out);
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