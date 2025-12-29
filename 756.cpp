#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 6;
const int C = 6;
const char A = 'A';
int mp[C][C];
int pyr[N][N];
int st[N][N];

class Solution {
   public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        int n = bottom.size();
        int m = allowed.size();
        for (int i = 0; i < C; i++) {
            for (int j = 0; j < C; j++) {
                mp[i][j] = 0;
            }
        }
        for (int i = 0; i < m; i++) {
            int x = allowed[i][0] - A;
            int y = allowed[i][1] - A;
            int z = allowed[i][2] - A;
            mp[x][y] |= (1 << z);
        }
        for (int i = 0; i < n; i++) {
            pyr[0][i] = bottom[i] - A;
        }
        st[0][0] = 0;
        int i = 0;
        int j = 0;
        bool res = false;
        while (true) {
            int t = st[i][j];
            int a = mp[pyr[i][j]][pyr[i][j + 1]];
            if (a == 0) {
                if (i == 0) {
                    break;
                }
                i--;
                j++;
                continue;
            }
            int pre = -1;
            if (j > 0) {
                pre = pyr[i + 1][j - 1];
            }
            for (; t < C; t++) {
                if (a & (1 << t)) {
                    if (pre == -1) {
                        break;
                    }
                    if (mp[pre][t] != 0) {
                        break;
                    }
                }
            }
            if (t == C) {
                j--;
                if (j < 0) {
                    if (i == 0) {
                        break;
                    }
                    j = n - 1 - i;
                    i--;
                }
                continue;
            }
            if (i == n - 2) {
                res = true;
                break;
            }
            pyr[i + 1][j] = t;
            st[i][j] = ++t;
            j++;
            if (j == n - 1 - i) {
                i++;
                j = 0;
            }
            st[i][j] = 0;
        }
        return res;
    }
};

int main() {
    string problemName = "756";
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
        auto bottom = jread_string(line_in);
        getline(file_in, line_in);
        auto allowed = jread_vector_string(line_in);
        auto res = sol.pyramidTransition(bottom, allowed);
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