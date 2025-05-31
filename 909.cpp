#include <unordered_set>
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
const int NMAX = 20;
bool isVisited[NMAX * NMAX + 1];
int q[NMAX * NMAX];

class Solution {
   public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        int goal = n * n;
        for (int i = 1; i < goal; i++) {
            isVisited[i] = false;
        }
        int l = 0;
        int r = 0;
        int roll = 0;
        q[r++] = 1;
        isVisited[1] = true;
        while (l < r) {
            roll++;
            int rold = r;
            while (l < rold) {
                int f = q[l++];
                for (int i = 1; i <= 6; i++) {
                    int nxt = f + i;
                    if (nxt == goal) {
                        return roll;
                    }
                    Node tmp = indexToPos(nxt, n);
                    int b = board[tmp.i][tmp.j];
                    if (b == goal) {
                        return roll;
                    }
                    if (b == -1) {
                        if (!isVisited[nxt]) {
                            q[r++] = nxt;
                            isVisited[nxt] = true;
                        }
                    } else {
                        if (!isVisited[b]) {
                            q[r++] = b;
                            isVisited[b] = true;
                        }
                    }
                }
            }
        }
        return -1;
    }

   private:
    Node indexToPos(int index, int n) {
        int n2 = n << 1;
        int q = (index - 1) / n2;
        int r = (index - 1) % n2;
        int i = n - 1 - (q << 1);
        int j = r;
        if (j >= n) {
            j = n2 - j - 1;
            i--;
        }
        return {i, j};
    }
};

int main() {
    string problemName = "909";
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
        auto board = jread_vector2d(line_in);
        auto res = sol.snakesAndLadders(board);
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