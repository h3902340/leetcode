#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    long long minMoves(vector<int>& balance) {
        int n = balance.size();
        int j = -1;
        ll total = 0;
        for (int i = 0; i < n; i++) {
            if (balance[i] < 0) {
                j = i;
            }
            total += balance[i];
        }
        if (total < 0) {
            return -1;
        }
        if (j == -1) {
            return 0;
        }
        int d = 1;
        int a = -balance[j];
        ll res = 0;
        while (a > 0) {
            int l = (j - d) % n;
            if (l < 0) {
                l += n;
            }
            int r = (j + d) % n;
            int b = balance[l] + balance[r];
            if (b < a) {
                res += (ll)b * d;
                a -= b;
                d++;
            } else {
                res += (ll)a * d;
                break;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3776";
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
        auto balance = jread_vector(line_in);
        auto res = sol.minMoves(balance);
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