#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MN = 1000;
const int U = 1024;
bool dp[MN][U];
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int end=m*n-1;
        for (int i = end; i >= 0; i--) {
            for (int j = 0; j < U; j++) {
                dp[i][j] = false;
            }
        }
        dp[0][grid[0][0]]=true;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i > 0) {
                    int q = i * n + j;
                    int p = (i-1) * n + j;
                    for (int k = 0; k < U; k++) {
                        if(dp[p][k]){
                            dp[q][k^grid[i][j]]=true;
                        }
                    }
                }
                if (j > 0) {
                    int q = i * n + j;
                    int p = i * n + j-1;
                    for (int k = 0; k < U; k++) {
                        if(dp[p][k]){
                            dp[q][k^grid[i][j]]=true;
                        }
                    }
                }
            }
        }
        for(int i=0;i<U;i++){
            if(dp[end][i]){
                return i;
            }
        }
        return -1;
    }
};

int main() {
    string problemName = "3882";
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
        auto grid = jread_vector2d(line_in);
        auto res = sol.minCost(grid);
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