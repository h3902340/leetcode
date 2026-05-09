#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int M = 50;
const int N = 50;
int buf[M * 2 + N * 2 - 4];
class Solution
{
public:
    vector<vector<int>> rotateGrid(vector<vector<int>> &grid, int k)
    {
        int m = grid.size();
        int n = grid[0].size();
        for (int i = min(m / 2, n / 2) - 1; i >= 0; i--)
        {
            int h = m - i * 2;
            int w = n - i * 2;
            int l = 0;
            for (int j = 0; j < w - 1; j++)
            {
                buf[l++] = grid[i][i + j];
            }
            for (int j = 0; j < h - 1; j++)
            {
                buf[l++] = grid[i + j][i + w - 1];
            }
            for (int j = 0; j < w - 1; j++)
            {
                buf[l++] = grid[i + h - 1][i + w - 1 - j];
            }
            for (int j = 0; j < h - 1; j++)
            {
                buf[l++] = grid[i + h - 1 - j][i];
            }
            int a = k;
            for (int j = 0; j < w - 1; j++)
            {
                grid[i][i + j] = buf[a++ % l];
            }
            for (int j = 0; j < h - 1; j++)
            {
                grid[i + j][i + w - 1] = buf[a++ % l];
            }
            for (int j = 0; j < w - 1; j++)
            {
                grid[i + h - 1][i + w - 1 - j] = buf[a++ % l];
            }
            for (int j = 0; j < h - 1; j++)
            {
                grid[i + h - 1 - j][i] = buf[a++ % l];
            }
        }
        return grid;
    }
};

int main()
{
    string problemName = "1914";
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
        auto grid = jread_vector2d(line_in);
        getline(file_in, line_in);
        int k = jread_int(line_in);
        auto res = sol.rotateGrid(grid, k);
        getline(file_out, line_out);
        auto ans = jread_vector2d(line_out);
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