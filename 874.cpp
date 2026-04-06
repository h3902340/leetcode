#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int L = -3e4;
const int U = 3e4;
vector<int> h[U - L + 1];
vector<int> v[U - L + 1];
class Solution {
   public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int n = commands.size();
        int m = obstacles.size();
        for (int i = 0; i < U - L + 1; i++) {
            h[i].clear();
            v[i].clear();
        }
        for (int i = 0; i < m; i++) {
            h[obstacles[i][0] - L].push_back(obstacles[i][1]);
            v[obstacles[i][1] - L].push_back(obstacles[i][0]);
        }
        for (int i = 0; i < U - L + 1; i++) {
            if (h[i].size() >= 2) {
                sort(begin(h[i]), end(h[i]));
            }
            if (v[i].size() >= 2) {
                sort(begin(v[i]), end(v[i]));
            }
        }
        int x = 0;
        int y = 0;
        int r = 0;
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (commands[i] == -1) {
                r = (r + 1) % 4;
            } else if (commands[i] == -2) {
                r = (r + 3) % 4;
            } else {
                if (r == 0) {
                    int a = 0;
                    int b = h[x - L].size() - 1;
                    int c = -1;
                    while (a <= b) {
                        int mid = (a + b) >> 1;
                        if (h[x - L][mid] > y) {
                            c = mid;
                            b = mid - 1;
                        } else {
                            a = mid + 1;
                        }
                    }
                    if (c == -1 || h[x - L][c] > y + commands[i]) {
                        y += commands[i];
                    } else {
                        y = h[x - L][c] - 1;
                    }
                } else if (r == 1) {
                    int a = 0;
                    int b = v[y - L].size() - 1;
                    int c = -1;
                    while (a <= b) {
                        int mid = (a + b) >> 1;
                        if (v[y - L][mid] > x) {
                            c = mid;
                            b = mid - 1;
                        } else {
                            a = mid + 1;
                        }
                    }
                    if (c == -1 || v[y - L][c] > x + commands[i]) {
                        x += commands[i];
                    } else {
                        x = v[y - L][c] - 1;
                    }
                } else if (r == 2) {
                    int a = 0;
                    int b = h[x - L].size() - 1;
                    int c = -1;
                    while (a <= b) {
                        int mid = (a + b) >> 1;
                        if (h[x - L][mid] < y) {
                            c = mid;
                            a = mid + 1;
                        } else {
                            b = mid - 1;
                        }
                    }
                    if (c == -1 || h[x - L][c] < y - commands[i]) {
                        y -= commands[i];
                    } else {
                        y = h[x - L][c] + 1;
                    }
                } else {
                    int a = 0;
                    int b = v[y - L].size() - 1;
                    int c = -1;
                    while (a <= b) {
                        int mid = (a + b) >> 1;
                        if (v[y - L][mid] < x) {
                            c = mid;
                            a = mid + 1;
                        } else {
                            b = mid - 1;
                        }
                    }
                    if (c == -1 || v[y - L][c] < x - commands[i]) {
                        x -= commands[i];
                    } else {
                        x = v[y - L][c] + 1;
                    }
                }
                res = max(res, x * x + y * y);
            }
        }
        return res;
    }
};

int main() {
    string problemName = "874";
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
        auto commands = jread_vector(line_in);
        getline(file_in, line_in);
        auto obstacles = jread_vector2d(line_in);
        auto res = sol.robotSim(commands, obstacles);
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