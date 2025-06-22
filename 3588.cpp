#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int min;
    int max;
};
const int LO = 1 - 1;
const int HI = 1e6 + 1;
Data mpx[HI];
Data mpy[HI];

#define ll long long
class Solution {
   public:
    long long maxArea(vector<vector<int>>& coords) {
        Data allx = {HI, LO};
        Data ally = {HI, LO};
        for (auto& c : coords) {
            int x = c[0];
            int y = c[1];
            mpx[x].min = HI;
            mpx[x].max = LO;
            mpy[y].min = HI;
            mpy[y].max = LO;
            allx.min = min(allx.min, x);
            allx.max = max(allx.max, x);
            ally.min = min(ally.min, y);
            ally.max = max(ally.max, y);
        }
        for (auto& c : coords) {
            int x = c[0];
            int y = c[1];
            mpx[x].min = min(mpx[x].min, y);
            mpx[x].max = max(mpx[x].max, y);
            mpy[y].min = min(mpy[y].min, x);
            mpy[y].max = max(mpy[y].max, x);
        }
        ll res = -1;
        ll a = -1;
        for (auto& c : coords) {
            int x = c[0];
            int y = c[1];
            Data& e = mpx[x];
            int width = e.max - e.min;
            a = (ll)abs(x - allx.min) * width;
            res = max(res, a);
            a = (ll)abs(x - allx.max) * width;
            res = max(res, a);
            Data& f = mpy[y];
            int height = f.max - f.min;
            a = (ll)abs(y - ally.min) * height;
            res = max(res, a);
            a = (ll)abs(y - ally.max) * height;
            res = max(res, a);
        }
        if (res == 0) {
            return -1;
        }
        return res;
    }
};

int main() {
    string problemName = "3588";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    while (getline(file_in, line_in)) {
        auto coords = jread_vector2d(line_in);
        auto res = sol.maxArea(coords);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(res, "res");
        jprint(ans, "ans");
        printf("\n");
    }
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}