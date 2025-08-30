#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int DIM = 9;
int mp[DIM];
class Solution {
   public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < DIM; i++) {
            for (int j = 0; j < DIM; j++) {
                mp[j] = 0;
            }
            for (int j = 0; j < DIM; j++) {
                if (board[i][j] == '.') {
                    continue;
                }
                int key = board[i][j] - '1';
                mp[key]++;
                if (mp[key] == 2) {
                    return false;
                }
            }
        }
        for (int j = 0; j < DIM; j++) {
            for (int i = 0; i < DIM; i++) {
                mp[i] = 0;
            }
            for (int i = 0; i < DIM; i++) {
                if (board[i][j] == '.') {
                    continue;
                }
                int key = board[i][j] - '1';
                mp[key]++;
                if (mp[key] == 2) {
                    return false;
                }
            }
        }
        for (int i = 0; i < DIM; i += 3) {
            for (int j = 0; j < DIM; j += 3) {
                for (int k = 0; k < DIM; k++) {
                    mp[k] = 0;
                }
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        int ch = board[i + k][j + l];
                        if (ch == '.') {
                            continue;
                        }
                        int key = ch - '1';
                        mp[key]++;
                        if (mp[key] == 2) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
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