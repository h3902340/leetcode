#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data
{
    int v;
    int i;
};
class SnapshotArray
{
public:
    vector<vector<Data>> a;
    int id;
    SnapshotArray(int length)
    {
        id = 0;
        a = vector<vector<Data>>(length, vector<Data>());
    }

    void set(int index, int val)
    {
        a[index].push_back({val, id});
    }

    int snap()
    {
        return id++;
    }

    int get(int index, int snap_id)
    {
        int l = 0;
        int r = a[index].size() - 1;
        int mx = -1;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (a[index][mid].i > snap_id)
            {
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
                mx = mid;
            }
        }
        if (mx == -1)
        {
            return 0;
        }
        return a[index][mx].v;
    }
};

int main()
{
    string problemName = "1146";
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
        auto res = sol.canPartitionGrid(grid);
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