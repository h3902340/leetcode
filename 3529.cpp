#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Node {
    int i;
    int j;
};
const int MMAX = 1e3;
const int NMAX = 1e3;
const int PMAX = 1e5;
int failure[PMAX];
int unionH[MMAX][NMAX];
int unionV[MMAX][NMAX];

class Solution {
   public:
    int countCells(vector<vector<char>>& grid, string pattern) {
        int m = grid.size();
        int n = grid[0].size();
        int p = pattern.size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                unionH[i][j] = 0;
                unionV[i][j] = 0;
            }
        }
        buildFailure(pattern, p);
        vector<Node> h = KMP(grid, pattern, m, n, p);
        vector<Node> v = KMP_vertical(grid, pattern, m, n, p);
        for (auto& e : h) {
            Node start = calcPosH(e, -p + 1, n);
            Node end = calcPosH(e, 1, n);
            unionH[start.i][start.j]++;
            unionH[end.i][end.j]--;
        }
        Node cur = {0, 0};
        while (cur.i != m - 1 || cur.j != n - 1) {
            Node nxt = calcPosH(cur, 1, n);
            unionH[nxt.i][nxt.j] += unionH[cur.i][cur.j];
            cur = nxt;
        }
        for (auto& e : v) {
            Node start = calcPosV(e, -p + 1, m);
            Node end = calcPosV(e, 1, m);
            unionV[start.i][start.j]++;
            unionV[end.i][end.j]--;
        }
        int res = 0;
        cur = {0, 0};
        if (unionH[cur.i][cur.j] && unionV[cur.i][cur.j]) {
            res++;
        }
        while (cur.i != m - 1 || cur.j != n - 1) {
            Node nxt = calcPosV(cur, 1, m);
            unionV[nxt.i][nxt.j] += unionV[cur.i][cur.j];
            cur = nxt;
            if (unionH[cur.i][cur.j] && unionV[cur.i][cur.j]) {
                res++;
            }
        }
        return res;
    }

   private:
    void buildFailure(string pattern, int p) {
        failure[0] = 0;
        for (int i = 1; i < p; i++) {
            int j = failure[i - 1];
            while (true) {
                if (pattern[j] == pattern[i]) {
                    failure[i] = j + 1;
                    break;
                }
                if (j == 0) {
                    failure[i] = 0;
                    break;
                }
                j = failure[j - 1];
            }
        }
    }
    vector<Node> KMP(vector<vector<char>>& grid, string pattern, int m, int n,
                     int p) {
        vector<Node> res;
        int k = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                while (true) {
                    if (grid[i][j] == pattern[k]) {
                        k++;
                        if (k == p) {
                            res.push_back({i, j});
                            k = failure[k - 1];
                        }
                        break;
                    }
                    if (k == 0) {
                        break;
                    }
                    k = failure[k - 1];
                }
            }
        }
        return res;
    }
    vector<Node> KMP_vertical(vector<vector<char>>& grid, string pattern, int m,
                              int n, int p) {
        vector<Node> res;
        int k = 0;
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                while (true) {
                    if (grid[i][j] == pattern[k]) {
                        k++;
                        if (k == p) {
                            res.push_back({i, j});
                            k = failure[k - 1];
                        }
                        break;
                    }
                    if (k == 0) {
                        break;
                    }
                    k = failure[k - 1];
                }
            }
        }
        return res;
    }
    Node calcPosH(Node e, int dis, int n) {
        e.j += dis;
        if (e.j < 0) {
            int q = (-e.j - 1) / n + 1;
            e.j += q * n;
            e.i -= q;
        } else if (e.j >= n) {
            int q = e.j / n;
            e.j -= q * n;
            e.i += q;
        }
        return e;
    }
    Node calcPosV(Node e, int dis, int m) {
        e.i += dis;
        if (e.i < 0) {
            int q = (-e.i - 1) / m + 1;
            e.i += q * m;
            e.j -= q;
        } else if (e.i >= m) {
            int q = e.i / m;
            e.i -= q * m;
            e.j += q;
        }
        return e;
    }
};

int main() {
    string problemName = "3529";
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
        auto grid = jread_vector2d_char(line_in);
        getline(file_in, line_in);
        auto pattern = jread_string(line_in);
        auto res = sol.countCells(grid, pattern);
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
        // jprint_vector2d_char(grid, "grid");
        // jprint_string(pattern, "pattern");
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