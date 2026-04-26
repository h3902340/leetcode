#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 15e3;
const int K = 25;
ll arr[N];
int p[K];
class Solution {
   public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        int n = points.size();
        for (int i = 0; i < n; i++) {
            int x = points[i][0];
            int y = points[i][1];
            if (x == 0) {
                arr[i] = y;
            } else if (y == side) {
                arr[i] = side + x;
            } else if (x == side) {
                arr[i] = (ll)side * 3 - y;
            } else {
                arr[i] = (ll)side * 4 - x;
            }
        }
        sort(begin(arr), begin(arr) + n);
        int l = 1;
        int r = side;
        int res = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            bool ok = true;
            for (int j = 0; j < n; j++) {
                p[0] = j;
                ll cur = arr[j];
                for (int i = 1; i < k; i++) {
                    int a = p[i - 1] + 1;
                    int b = n - 1;
                    int d = -1;
                    while (a <= b) {
                        int c = (a + b) >> 1;
                        if (arr[c] - cur < mid) {
                            a = c + 1;
                        } else {
                            d = c;
                            b = c - 1;
                        }
                    }
                    if (d == -1) {
                        ok = false;
                        break;
                    }
                    p[i] = d;
                    cur = arr[d];
                }
                if (!ok) {
                    break;
                }
                if (arr[p[0]] + (ll)side * 4 - arr[p[k - 1]] >= mid) {
                    break;
                }
            }
            if (ok) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3464";
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
        auto side = jread_int(line_in);
        getline(file_in, line_in);
        auto points = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.maxDistance(side, points, k);
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