#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// TODO: Finding left and right can also be done using RMQ, the time complexity overall will be reduced
// from O(nlogn + mlogn) to O(nlogn + m), might be faster.
struct Seg {
    int end;
    int len;
};
const int NMAX = 1e5;
const int ZOZMAX = (NMAX - 1) >> 1;
const int LOGZOZMAX = 17;
Seg segs[NMAX];
Seg zeroOneZero[ZOZMAX][3];
int rmq[ZOZMAX][LOGZOZMAX];

class Solution {
   public:
    vector<int> maxActiveSectionsAfterTrade(string s,
                                            vector<vector<int>>& queries) {
        int n = s.size();
        int m = queries.size();
        int t = 0;
        bool isFirstOne = s[0] == '1';
        int cur = s[0];
        int seg = 1;
        int totalActive = 0;
        for (int i = 1; i < n; i++) {
            if (s[i] == cur) {
                seg++;
            } else {
                if ((t + isFirstOne) & 1) {
                    totalActive += seg;
                }
                segs[t++] = {i - 1, seg};
                seg = 1;
                cur = s[i];
            }
        }
        if ((t + isFirstOne) & 1) {
            totalActive += seg;
        }
        segs[t++] = {n - 1, seg};
        int u = 0;
        for (int i = isFirstOne; i < t - 2; i += 2) {
            for (int j = 0; j < 3; j++) {
                zeroOneZero[u][j] = segs[i + j];
            }
            u++;
        }
        if (u == 0) {
            vector<int> res(m);
            for (int i = 0; i < m; i++) {
                res[i] = totalActive;
            }
            return res;
        }
        int lgu = log2(u) + 1;
        for (int i = 0; i < u; i++) {
            rmq[i][0] = zeroOneZero[i][0].len + zeroOneZero[i][2].len;
        }
        int k = 1;
        for (int j = 1; j < lgu; j++) {
            int tmp = u - (k << 1) + 1;
            for (int i = 0; i < tmp; i++) {
                int a = rmq[i][j - 1];
                int b = rmq[i + k][j - 1];
                rmq[i][j] = max(a, b);
            }
            k <<= 1;
        }
        vector<int> res(m);
        for (int i = 0; i < m; i++) {
            int x = queries[i][0];
            int y = queries[i][1];
            int l = 0;
            int r = u - 1;
            int left = u;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (x > zeroOneZero[mid][0].end) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                    left = mid;
                }
            }
            l = 0;
            r = u - 1;
            int right = -1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (y > zeroOneZero[mid][2].end - zeroOneZero[mid][2].len) {
                    l = mid + 1;
                    right = mid;
                } else {
                    r = mid - 1;
                }
            }
            if (left > right) {
                res[i] = totalActive;
                continue;
            }
            int a = left + 1;
            int b = right - 1;
            int maxActive = 0;
            if (a <= b) {
                int d = log2(b - a + 1);
                maxActive = max(rmq[a][d], rmq[b - (1 << d) + 1][d]);
            }
            int maxLeft = 0;
            if (x >= zeroOneZero[left][0].end - zeroOneZero[left][0].len + 1) {
                maxLeft += zeroOneZero[left][0].end - x + 1;
            } else {
                maxLeft += zeroOneZero[left][0].len;
            }
            if (y <= zeroOneZero[left][2].end) {
                maxLeft +=
                    y - zeroOneZero[left][2].end + zeroOneZero[left][2].len;
            } else {
                maxLeft += zeroOneZero[left][2].len;
            }
            int maxRight = 0;
            if (x >=
                zeroOneZero[right][0].end - zeroOneZero[right][0].len + 1) {
                maxRight += zeroOneZero[right][0].end - x + 1;
            } else {
                maxRight += zeroOneZero[right][0].len;
            }
            if (y <= zeroOneZero[right][2].end) {
                maxRight +=
                    y - zeroOneZero[right][2].end + zeroOneZero[right][2].len;
            } else {
                maxRight += zeroOneZero[right][2].len;
            }
            if (maxActive < maxLeft) {
                maxActive = maxLeft;
            }
            if (maxActive < maxRight) {
                maxActive = maxRight;
            }
            res[i] = totalActive + maxActive;
        }
        return res;
    }
};

int main() {
    string problemName = "3501";
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
        auto s = jread_string(line_in);
        getline(file_in, line_in);
        auto queries = jread_vector2d(line_in);
        auto res = sol.maxActiveSectionsAfterTrade(s, queries);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_string(s, "s");
        jprint_vector2d(queries, "queries");
        jprint_vector(res, "res");
        jprint_vector(ans, "ans");
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