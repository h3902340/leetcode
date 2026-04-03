#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Robot {
    int p;
    int d;
    bool operator<(const Robot& a) const { return p < a.p; }
};
const int N = 1e5;
Robot bot[N];
class Solution {
   public:
    int maxWalls(vector<int>& robots, vector<int>& distance,
                 vector<int>& walls) {
        int n = robots.size();
        int m = walls.size();
        for (int i = 0; i < n; i++) {
            bot[i] = {robots[i], distance[i]};
        }
        sort(begin(bot), begin(bot) + n);
        sort(begin(walls), end(walls));
        Robot pre = {INT32_MIN, 0};
        int x = 0;
        int y = 0;
        for (int i = 0; i < n; i++) {
            int x2 = 0;
            int y2 = 0;
            int l = max(bot[i].p - bot[i].d - 1, pre.p);
            int a = x + f(bot[i].p, walls, m) - f(l, walls, m);
            l = max(l, pre.p + pre.d);
            int b = y + f(bot[i].p, walls, m) - f(l, walls, m);
            x2 = max(a, b);
            int r = bot[i].p + bot[i].d;
            if (i < n - 1) {
                r = min(r, bot[i + 1].p);
            }
            l = bot[i].p - 1;
            y2 = x + f(r, walls, m) - f(l, walls, m);
            if (pre.p + pre.d >= bot[i].p) {
                l++;
            }
            y2 = max(y2, y + f(r, walls, m) - f(l, walls, m));
            x = x2;
            y = y2;
            pre = bot[i];
        }
        return max(x, y);
    }
    int f(int p, vector<int>& walls, int m) {
        int l = 0;
        int r = m - 1;
        int res = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (p < walls[mid]) {
                r = mid - 1;
            } else {
                res = mid;
                l = mid + 1;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3661";
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
        auto robots = jread_vector(line_in);
        getline(file_in, line_in);
        auto distance = jread_vector(line_in);
        getline(file_in, line_in);
        auto walls = jread_vector(line_in);
        auto res = sol.maxWalls(robots, distance, walls);
        getline(file_out, line_out);
        auto ans = jread_int(line_out);
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