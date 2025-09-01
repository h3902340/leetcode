#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Position {
    int i;
    int j;
};
const int DIM = 9;
const int ALL = (1 << DIM) - 1;
int row[DIM];
int col[DIM];
int grid[DIM];
Position holes[DIM * DIM];
int holeCNT;

class Solution {
   public:
    void solveSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < DIM; i++) {
            row[i] = ALL;
            col[i] = ALL;
            grid[i] = ALL;
        }
        holeCNT = 0;
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                if (board[i][j] == '.') {
                    holes[holeCNT++] = {i, j};
                } else {
                    fill(i, j, board[i][j] - '1');
                }
            }
        }
        solver(board, 0);
    }
    bool solver(vector<vector<char>>& board, int k) {
        if (k == holeCNT) {
            return true;
        }
        int i = holes[k].i;
        int j = holes[k].j;
        for (int c = 0; c < DIM; c++) {
            if (canFill(i, j, c)) {
                fill(i, j, c);
                board[i][j] = c + '1';
                if (solver(board, k + 1)) {
                    return true;
                }
                erase(i, j, c);
            }
        }
        return false;
    }
    void fill(int i, int j, int c) {
        int mask = 1 << c;
        row[i] ^= mask;
        col[j] ^= mask;
        int a = gridIdx(i, j);
        grid[a] ^= mask;
    }
    void erase(int i, int j, int c) {
        int mask = 1 << c;
        row[i] ^= mask;
        col[j] ^= mask;
        int a = gridIdx(i, j);
        grid[a] ^= mask;
    }
    bool canFill(int i, int j, int c) {
        int mask = 1 << c;
        int a = gridIdx(i, j);
        return row[i] & mask && col[j] & mask && grid[a] & mask;
    }
    int gridIdx(int i, int j) { return (i / 3) * 3 + j / 3; }
};

int main() {
    string problemName = "37";
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
        sol.solveSudoku(board);
        getline(file_out, line_out);
        auto ans = jread_vector2d_char(line_out);
        printf("Case %d", ++caseCount);
        if (board == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(board, "res");
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