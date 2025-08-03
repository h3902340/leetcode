#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();
        for (int i = 1; i < n; i++) {
            fruits[i][1] += fruits[i - 1][1];
        }
        int i = findLeft(fruits, startPos - k, n, false);
        int j = findLeft(fruits, startPos, n, true);
        int res = 0;
        if (j >= 0) {
            res = fruits[j][1];
        }
        if (i >= 0) {
            res -= fruits[i][1];
        }
        j++;
        while (j < n) {
            int left = startPos - fruits[i + 1][0];
            int right = fruits[j][0] - startPos;
            if (left < 0) {
                if (k < right) {
                    break;
                }
            } else if (k < left + right * 2 && k < right + left * 2) {
                i++;
                continue;
            }
            int a = fruits[j][1];
            if (i >= 0) {
                a -= fruits[i][1];
            }
            res = max(res, a);
            j++;
        }
        return res;
    }
    int findLeft(vector<vector<int>>& fruits, int i, int n, bool inclusive) {
        int l = 0;
        int r = n - 1;
        int res = -1;
        if (inclusive) {
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (i < fruits[mid][0]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                    res = mid;
                }
            }
        } else {
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (i <= fruits[mid][0]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                    res = mid;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2106";
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
        auto fruits = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto startPos = jread_int(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.maxTotalFruits(fruits, startPos, k);
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