#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int n = piles.size();
        int max = piles[0];
        for (int i = 1; i < n; i++) {
            if (max < piles[i]) {
                max = piles[i];
            }
        }
        int l = 1;
        int r = max;
        int min = r;
        while (l <= r) {
            int mid = (l + r) >> 1;
            long long c = 0;
            for (int i = 0; i < n; i++) {
                c += (piles[i] - 1) / mid + 1;
            }
            if (c > h) {
                l = mid + 1;
            } else {
                r = mid - 1;
                min = mid;
            }
        }
        return min;
    }
};

int main() {
    string problemName = "875";
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
        auto piles = jread_vector(line_in);
        getline(file_in, line_in);
        auto h = jread_int(line_in);
        auto res = sol.minEatingSpeed(piles, h);
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