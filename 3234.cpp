#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 4e4;
int pre[N + 1];
// time: O(NlogN), space: O(N)
class Solution {
   public:
    int numberOfSubstrings(string s) {
        int n = s.size();
        int res = 0;
        int sz = 1;
        int cnt = 0;
        pre[0] = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                pre[sz] = cnt;
                pre[sz] += pre[sz - 1];
                if (cnt > 0) {
                    res += (((cnt + 1) * cnt) >> 1);
                    cnt = 0;
                }
                sz++;
            } else {
                cnt++;
            }
        }
        pre[sz] = cnt;
        pre[sz] += pre[sz - 1];
        if (cnt > 0) {
            res += (((cnt + 1) * cnt) >> 1);
        }
        sz++;
        if (res == 0) {
            return 0;
        }
        for (int z = 1; z < sz; z++) {
            int one = z * z;
            if (z + one > n) {
                break;
            }
            for (int i = 1; i + z < sz; i++) {
                if (pre[i + z] - pre[i - 1] < one) {
                    continue;
                }
                int d = one - (pre[i + z - 1] - pre[i]);
                int l = pre[i] - pre[i - 1] + 1;
                int r = pre[i + z] - pre[i + z - 1] + 1;
                if (d > 0) {
                    if (l > d) {
                        res += (l - d) * r;
                    }
                    int ll = min(l, d);
                    int rr = r - d + ll;
                    int h = min(ll, rr);
                    res += rr * h - ((h + 1) * h >> 1);
                } else {
                    res += l * r;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3234";
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
        auto res = sol.numberOfSubstrings(s);
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