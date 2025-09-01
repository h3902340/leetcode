#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int DIM = 9;
int mp[DIM * 3];
class Solution {
   public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < DIM; i++) {
            memset(mp, 0, sizeof(mp));
            for (int j = 0; j < DIM; j++) {
                bool res = isValid(board[i][j], 0);
                if (!res) {
                    return false;
                }
                res = isValid(board[j][i], 1);
                if (!res) {
                    return false;
                }
                int x = (i / 3) * 3 + j / 3;
                int y = (i % 3) * 3 + j % 3;
                res = isValid(board[x][y], 2);
                if (!res) {
                    return false;
                }
            }
        }
        return true;
    }
    bool isValid(char c, int idx) {
        if (c == '.') {
            return true;
        }
        int key = c - '1' + idx * DIM;
        mp[key]++;
        return mp[key] == 1;
    }
};

int main() {
    string problemName = "36";
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
        auto board = jread_vector2d_char(line_in);
        auto res = sol.isValidSudoku(board);
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