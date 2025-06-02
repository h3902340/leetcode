#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Node {
    int i;
    int j;
    int energy;
    int litter;
    int move;
};
const int M = 20;
const int N = 20;
const int E = 50;
const int L = 10;
const int dir[4][2]{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
Node q[M * N * E * (1 << L)];
int vis[M][N][1 << L];
int litterMap[M][N];

class Solution {
   public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        int l = 0;
        int r = 0;
        int totalLitter = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int c = classroom[i][j];
                if (c == 'S') {
                    Node node = {i, j, energy, 0, 0};
                    q[r++] = node;
                } else {
                    if (c == 'L') {
                        litterMap[i][j] = totalLitter;
                        totalLitter++;
                    }
                }
            }
        }
        totalLitter = (1 << totalLitter) - 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int l = 0; l <= totalLitter; l++) {
                    vis[i][j][l] = -1;
                }
            }
        }
        vis[q[0].i][q[0].j][0] = energy;
        int min = INT32_MAX;
        bool success = false;
        while (l < r) {
            Node f = q[l++];
            if (f.litter == totalLitter) {
                if (min > f.move) {
                    min = f.move;
                }
                success = true;
            }
            if (f.energy == 0) {
                continue;
            }
            for (int i = 0; i < 4; i++) {
                int a = f.i + dir[i][0];
                int b = f.j + dir[i][1];
                if (a < 0 || a >= m || b < 0 || b >= n) {
                    continue;
                }
                int c = classroom[a][b];
                if (c == 'X') continue;
                if (c == 'L') {
                    int bit = 1 << litterMap[a][b];
                    if (vis[a][b][f.litter | bit] >= f.energy - 1) {
                        continue;
                    }
                    Node node = {a, b, f.energy - 1, f.litter | bit,
                                 f.move + 1};
                    q[r++] = node;
                    vis[a][b][node.litter] = node.energy;
                } else if (c == 'R') {
                    if (vis[a][b][f.litter] == energy) {
                        continue;
                    }
                    Node node = {a, b, energy, f.litter, f.move + 1};
                    q[r++] = node;
                    vis[a][b][node.litter] = energy;
                } else {
                    if (vis[a][b][f.litter] >= f.energy - 1) {
                        continue;
                    }
                    Node node = {a, b, f.energy - 1, f.litter, f.move + 1};
                    q[r++] = node;
                    vis[a][b][node.litter] = node.energy;
                }
            }
        }
        if (success) {
            return min;
        }
        return -1;
    }
};

int main() {
    string problemName = "3568";
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
        auto classroom = jread_vector_string(line_in);
        getline(file_in, line_in);
        auto energy = jread_int(line_in);
        auto res = sol.minMoves(classroom, energy);
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
        jprint_vector_string(classroom, "classroom");
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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