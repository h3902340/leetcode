#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minimumIndex(vector<int>& capacity, int itemSize) {
        int n = capacity.size();
        int mn = INT32_MAX;
        int mni = -1;
        for (int i = 0; i < n; i++) {
            if (capacity[i] > itemSize) {
                if (mn > capacity[i]) {
                    mn = capacity[i];
                    mni = i;
                }
            } else if (capacity[i] == itemSize) {
                return i;
            }
        }
        return mni;
    }
};

int main() {
    string problemName = "3861";
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
        auto capacity = jread_vector(line_in);
        getline(file_in, line_in);
        auto itemSize = jread_int(line_in);
        auto res = sol.minimumIndex(capacity, itemSize);
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