#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int ROW = 1000;
const int C = 26;
const int BASE = 10;
const int A = 'A';
const int ZERO = '0';
const int PLUS = '+';
const int EQUAL = '=';
int table[ROW + 1][C];
class Spreadsheet {
   public:
    Spreadsheet(int rows) {
        for (int i = 0; i <= ROW; i++) {
            for (int j = 0; j < C; j++) {
                table[i][j] = 0;
            }
        }
    }

    void setCell(string cell, int value) {
        int col = cell[0] - A;
        int row = 0;
        for (int i = 1; i < cell.size(); i++) {
            row = row * BASE + (cell[i] - ZERO);
        }
        table[row][col] = value;
    }

    void resetCell(string cell) {
        int col = cell[0] - A;
        int row = 0;
        for (int i = 1; i < cell.size(); i++) {
            row = row * BASE + (cell[i] - ZERO);
        }
        table[row][col] = 0;
    }

    int getValue(string formula) {
        int i = 1;
        int a = 0;
        int col = formula[i] - A;
        if (col >= 0) {
            int row = 0;
            i++;
            for (; i < formula.size(); i++) {
                if (formula[i] == PLUS) break;
                row = row * BASE + (formula[i] - ZERO);
            }
            a = table[row][col];
        } else {
            for (; i < formula.size(); i++) {
                if (formula[i] == PLUS) break;
                a = a * BASE + (formula[i] - ZERO);
            }
        }
        i++;
        int b = 0;
        col = formula[i] - A;
        if (col >= 0) {
            int row = 0;
            i++;
            for (; i < formula.size(); i++) {
                if (formula[i] == EQUAL) break;
                row = row * BASE + (formula[i] - ZERO);
            }
            b = table[row][col];
        } else {
            for (; i < formula.size(); i++) {
                b = b * BASE + (formula[i] - ZERO);
            }
        }
        return a + b;
    }
};

int main() {
    string problemName = "3484";
    auto begin = jtimer();
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    vector<int> res;
    Spreadsheet sol = Spreadsheet(3);
    res.push_back(-1);
    res.push_back(sol.getValue("=5+7"));
    sol.setCell("A1", 10);
    res.push_back(-1);
    res.push_back(sol.getValue("=A1+6"));
    sol.setCell("B2", 15);
    res.push_back(-1);
    res.push_back(sol.getValue("=A1+B2"));
    sol.resetCell("A1");
    res.push_back(-1);
    res.push_back(sol.getValue("=A1+B2"));
    vector<int> ans = {-1, 12, -1, 16, -1, 25, -1, 15};
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
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}