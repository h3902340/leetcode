#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int QMAX = 4;
struct Node {
    int l[QMAX];
    int r[QMAX];
    int lt;
    int rt;
    int v;
};
const int NMAX = 1e5;
const int LGNMAX = 17;
Node dp[NMAX][LGNMAX];

class Solution {
   public:
    vector<int> maxActiveSectionsAfterTrade(string s,
                                            vector<vector<int>>& queries) {
        int n = s.size();
        int m = queries.size();
        const int lgn = log2(n) + 1;
        int totalActive = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < lgn; j++) {
                dp[i][j].lt = 0;
                dp[i][j].rt = QMAX - 1;
            }
            Node& e = dp[i][0];
            if (s[i] == '0') {
                e.l[e.lt] = -1;
                e.r[e.rt] = -1;
            } else {
                e.l[e.lt] = 1;
                e.r[e.rt] = 1;
                totalActive++;
            }
            e.v = 0;
        }
        int k = 1;
        for (int j = 1; j < lgn; j++) {
            int tmp = n - (k << 1) + 1;
            for (int i = 0; i < tmp; i++) {
                Node& a = dp[i][j - 1];
                Node& b = dp[i + k][j - 1];
                dp[i][j] = merge(a, b);
            }
            k <<= 1;
        }
        vector<int> res(m);
        for (int i = 0; i < m; i++) {
            int l = queries[i][0];
            int r = queries[i][1];
            int d = log2(r - l + 1);
            Node temp = dp[l][d];
            l += (1 << d);
            while (l <= r) {
                d = log2(r - l + 1);
                temp = merge(temp, dp[l][d]);
                l += (1 << d);
            }
            res[i] = temp.v + totalActive;
        }
        return res;
    }

   private:
    Node merge(Node& a, Node& b) {
        Node c;
        c.lt = a.lt;
        c.rt = b.rt;
        c.v = 0;
        for (int x = 0; x < QMAX; x++) {
            c.l[x] = a.l[x];
            c.r[x] = b.r[x];
        }
        int l = 0;
        while (c.lt < QMAX && l <= b.lt) {
            if ((c.l[c.lt] > 0) == (b.l[l] > 0)) {
                c.l[c.lt] += b.l[l];
            } else {
                c.lt++;
                if (c.lt == QMAX) {
                    break;
                }
                c.l[c.lt] = b.l[l];
            }
            l++;
            if (l == QMAX) {
                break;
            }
        }
        int r = QMAX - 1;
        while (c.rt >= 0 && r >= a.rt) {
            if ((c.r[c.rt] > 0) == (a.r[r] > 0)) {
                c.r[c.rt] += a.r[r];
            } else {
                c.rt--;
                if (c.rt == -1) {
                    break;
                }
                c.r[c.rt] = a.r[r];
            }
            r--;
            if (r == -1) {
                break;
            }
        }
        if (c.lt >= QMAX - 1 && c.l[0] < 0 && c.l[1] > 0 && c.l[2] < 0) {
            int v = c.l[0] + c.l[2];
            v = -v;
            if (c.v < v) {
                c.v = v;
            }
        }
        if (c.rt <= 0 && c.r[QMAX - 3] < 0 && c.r[QMAX - 2] > 0 &&
            c.r[QMAX - 1] < 0) {
            int v = c.r[QMAX - 3] + c.r[QMAX - 1];
            v = -v;
            if (c.v < v) {
                c.v = v;
            }
        }
        if (c.v < a.v) {
            c.v = a.v;
        }
        if (c.v < b.v) {
            c.v = b.v;
        }
        if (a.r[QMAX - 1] > 0) {
            if (b.l[0] > 0) {
                if (a.rt <= QMAX - 2 && b.lt >= 1) {
                    int v = a.r[QMAX - 2] + b.l[1];
                    v = -v;
                    if (c.v < v) {
                        c.v = v;
                    }
                }
            } else {
                if (a.rt <= QMAX - 2) {
                    int v = a.r[QMAX - 2] + b.l[0];
                    v = -v;
                    if (c.v < v) {
                        c.v = v;
                    }
                }
            }
        } else {
            if (b.l[0] > 0) {
                if (a.rt <= QMAX - 1 && b.lt >= 1) {
                    int v = a.r[QMAX - 1] + b.l[1];
                    v = -v;
                    if (c.v < v) {
                        c.v = v;
                    }
                }
            } else {
                if (a.rt <= QMAX - 3) {
                    int v = a.r[QMAX - 3] + a.r[QMAX - 1] + b.l[0];
                    v = -v;
                    if (c.v < v) {
                        c.v = v;
                    }
                }
                if (b.lt >= 2) {
                    int v = a.r[QMAX - 1] + b.l[0] + b.l[2];
                    v = -v;
                    if (c.v < v) {
                        c.v = v;
                    }
                }
            }
        }
        return c;
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