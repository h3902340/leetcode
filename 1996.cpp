#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        int n = properties.size();
        sort(begin(properties), end(properties));
        vector<int> suf(n);
        suf[n - 1] = properties[n - 1][1];
        for (int i = n - 2; i >= 0; i--) {
            suf[i] = max(suf[i + 1], properties[i][1]);
        }
        int j = 1;
        int res = 0;
        for (int i = 0; i < n; i++) {
            while (j < n && properties[i][0] == properties[j][0]) {
                j++;
            }
            if (j == n) {
                break;
            }
            if (properties[i][1] < suf[j]) {
                res++;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1996";
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
        auto properties = jread_vector2d(line_in);
        auto res = sol.numberOfWeakCharacters(properties);
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