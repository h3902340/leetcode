#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 3e4;
const int KIND = 5;
int fre[KIND];
int diffMin[2][2];
int cnt[2][2];

class Solution {
   public:
    int maxDifference(string s, int k) {
        int n = s.size();
        for (int i = 0; i < KIND; i++) {
            fre[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            fre[s[i] - '0']++;
        }
        // 0 is an impossible answer, which can be used to tell if a valid
        // answer has been found. Similarly, if the question asks for the max of
        // "even-even" or "odd-odd", then 1 is the impossible answer.
        int res = 0;
        for (int a = 0; a < KIND; a++) {
            if (fre[a] == 0) continue;
            for (int b = 0; b < KIND; b++) {
                if (a == b) continue;
                if (fre[b] <= 1) continue;
                int tmp = maxTwoChar(s, k, a, b);
                if (res == 0 || (tmp != 0 && res < tmp)) {
                    res = tmp;
                }
            }
        }
        return res;
    }
    int maxTwoChar(string s, int k, int a, int b) {
        int n = s.size();
        diffMin[0][0] = 1;
        diffMin[0][1] = 0;
        diffMin[1][0] = 0;
        diffMin[1][1] = 1;
        cnt[0][0] = 0;
        cnt[0][1] = 0;
        cnt[1][0] = 0;
        cnt[1][1] = 0;
        int res = 0;
        int i = 0;
        for (int j = 0; j < n; j++) {
            int c = s[j] - '0';
            if (c == a) {
                cnt[1][0]++;
            } else if (c == b) {
                cnt[1][1]++;
            }
            if (cnt[1][0] < 1) continue;
            if (cnt[1][1] < 2) continue;
            if (j < k - 1) continue;
            while (j - i >= k && cnt[1][1] > cnt[0][1]) {
                int c = s[i] - '0';
                if (c == a) {
                    cnt[0][0]++;
                } else if (c == b) {
                    if (cnt[1][1] == cnt[0][1] + 1) {
                        break;
                    }
                    cnt[0][1]++;
                }
                bool oddA = cnt[0][0] & 1;
                bool oddB = cnt[0][1] & 1;
                int d = cnt[0][0] - cnt[0][1];
                if (diffMin[oddA][oddB] == !(oddA ^ oddB) ||
                    diffMin[oddA][oddB] > d) {
                    diffMin[oddA][oddB] = d;
                }
                i++;
            }
            bool oddA = cnt[1][0] & 1;
            bool oddB = cnt[1][1] & 1;
            if (oddA && !oddB) {
                int tmp = cnt[1][0] - cnt[1][1];
                if (res == 0 || res < tmp) {
                    res = tmp;
                }
            }
            if (diffMin[!oddA][oddB] == !(!oddA ^ oddB)) {
                continue;
            }
            int tmp = cnt[1][0] - cnt[1][1] - diffMin[!oddA][oddB];
            if (res == 0 || res < tmp) {
                res = tmp;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3445";
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
        auto k = jread_int(line_in);
        auto res = sol.maxDifference(s, k);
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
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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