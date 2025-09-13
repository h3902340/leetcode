#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// time: O(N^3), space: O(N^3)
const int N = 50;
vector<vector<int>> sol[N + 1];
bool isInit = false;
static void init() {
    int edge = 20;
    for (int i = 5; i <= N; i++) {
        sol[i] = vector<vector<int>>(edge);
        int half = i >> 1;
        bool isOdd = i & 1;
        int k = 0;
        for (int l = 2; l < half + isOdd; l++) {
            for (int j = 0; j < i; j++) {
                int a = (j + l) % i;
                sol[i][k++] = {j, a};
            }
            for (int j = 0; j < i; j++) {
                int a = (j + l) % i;
                sol[i][k++] = {a, j};
            }
        }
        if (isOdd) {
            int a = half;
            for (int j = 0; j < i; j++) {
                sol[i][k++] = {a, (a + 1) % i};
                a = (a + 2) % i;
            }
            for (int j = 0; j < i; j++) {
                sol[i][k++] = {(a + 1) % i, a};
                a = (a + 2) % i;
            }
        } else {
            for (int j = 0; j < half; j++) {
                int a = (j + half) % i;
                sol[i][k++] = {j, a};
            }
            for (int j = 0; j < half; j++) {
                int a = (j + half) % i;
                sol[i][k++] = {a, j};
            }
            for (int j = 0; j < i; j += 2) {
                sol[i][k++] = {j, j + 1};
            }
            for (int j = 0; j < i; j += 2) {
                sol[i][k++] = {j + 1, j};
            }
            for (int j = 1; j < i; j += 2) {
                sol[i][k++] = {j, (j + 1) % i};
            }
            for (int j = 1; j < i; j += 2) {
                sol[i][k++] = {(j + 1) % i, j};
            }
        }
        edge += i << 1;
    }
}

class Solution {
   public:
    vector<vector<int>> generateSchedule(int n) {
        if (!isInit) {
            init();
            isInit = true;
        }
        if (n < 5) {
            return {};
        }
        return sol[n];
    }
};

int main() {
    string problemName = "3680";
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
        auto n = jread_int(line_in);
        auto res = sol.generateSchedule(n);
        getline(file_out, line_out);
        printf("Case %d", ++caseCount);
        bool pass = true;
        if (n < 5) {
            if (res.size() > 0) {
                pass = false;
            }
        } else {
            vector<vector<int>> cnt(n, vector<int>(n));
            int preX = -1;
            int preY = -1;
            for (auto &e : res) {
                int x = e[0];
                int y = e[1];
                if (x == y) {
                    pass = false;
                    break;
                }
                cnt[x][y]++;
                if (cnt[x][y] == 2) {
                    pass = false;
                    break;
                }
                if (x == preX || x == preY || y == preX || y == preY) {
                    pass = false;
                    break;
                }
                preX = x;
                preY = y;
            }
        }
        if (pass) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(res, "res");
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