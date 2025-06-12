#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if (n == 1) {
            return 1;
        }
        int c = 1;
        int peak = 0;
        int cur = 1;
        int i = 0;
        while (i < n - 1 && ratings[i] == ratings[i + 1]) {
            c++;
            i++;
        }
        if (i == n - 1) {
            return c;
        }
        bool isUp = ratings[i] < ratings[i + 1];
        i++;
        for (; i < n - 1; i++) {
            cur++;
            if (ratings[i] == ratings[i + 1]) {
                if (peak == 0) {
                    c += cur;
                } else {
                    c += max(peak, cur);
                }
                cur = 0;
                peak = 0;
                continue;
            }
            if (ratings[i] < ratings[i + 1]) {
                if (!isUp) {
                    if (peak == 0) {
                        c += cur;
                    } else {
                        c += max(cur, peak);
                        peak = 0;
                    }
                    cur = 1;
                    isUp = true;
                } else {
                    c += cur;
                }
            } else {
                if (isUp) {
                    peak = cur;
                    c++;
                    cur = 1;
                    isUp = false;
                } else {
                    c += cur;
                }
            }
        }
        cur++;
        if (peak == 0) {
            c += cur;
        } else {
            c += max(cur, peak);
        }
        return c;
    }
};

int main() {
    string problemName = "135";
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
        auto ratings = jread_vector(line_in);
        auto res = sol.candy(ratings);
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
        // jprint(ratings, "ratings");
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