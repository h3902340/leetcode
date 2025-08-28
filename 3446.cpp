#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 10;
int temp[N];

class Solution {
   public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        for (int j = n - 1; j > 0; j--) {
            int idx = 0;
            int i = 0;
            int jold = j;
            while (i >= 0 && i < n && j >= 0 && j < n) {
                temp[idx++] = grid[i][j];
                i++;
                j++;
            }
            sort(begin(temp), begin(temp) + idx);
            i = 0;
            j = jold;
            for (int k = 0; k < idx; k++) {
                grid[i][j] = temp[k];
                i++;
                j++;
            }
            j = jold;
        }
        for (int i = 0; i < n; i++) {
            int idx = 0;
            int iold = i;
            int j = 0;
            while (i >= 0 && i < n && j >= 0 && j < n) {
                temp[idx++] = grid[i][j];
                i++;
                j++;
            }
            sort(begin(temp), begin(temp) + idx, greater<int>());
            i = iold;
            j = 0;
            for (int k = 0; k < idx; k++) {
                grid[i][j] = temp[k];
                i++;
                j++;
            }
            i = iold;
        }
        return grid;
    }
};

int main() {
    string problemName = "3446";
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
        auto res = sol.sortMatrix(grid);
        getline(file_out, line_out);
        auto ans = jread_vector2d(line_out);
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