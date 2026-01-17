#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<int> bestTower(vector<vector<int>>& towers, vector<int>& center,
                          int radius) {
        int n = towers.size();
        int idx = -1;
        int mx = -1;
        for (int i = 0; i < n; i++) {
            int d =
                abs(towers[i][0] - center[0]) + abs(towers[i][1] - center[1]);
            if (d <= radius) {
                if (mx < towers[i][2]) {
                    mx = towers[i][2];
                    idx = i;
                } else if (mx == towers[i][2]) {
                    if (towers[idx][0] > towers[i][0]) {
                        idx = i;
                    } else if (towers[idx][0] == towers[i][0]) {
                        if (towers[idx][1] > towers[i][1]) {
                            idx = i;
                        }
                    }
                }
            }
        }
        if (idx == -1) {
            return {-1, -1};
        }
        return {towers[idx][0], towers[idx][1]};
    }
};

int main() {
    string problemName = "3809";
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
        auto towers = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto center = jread_vector(line_in);
        getline(file_in, line_in);
        auto radius = jread_int(line_in);
        auto res = sol.bestTower(towers, center, radius);
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