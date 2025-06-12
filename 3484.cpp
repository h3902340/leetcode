#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Spreadsheet {
   public:
    vector<vector<int>> table;
    Spreadsheet(int rows) {
        table = vector<vector<int>>(rows + 1, vector<int>(26));
    }

    void setCell(string cell, int value) {
        int col = cell[0] - 'A';
        int row = 0;
        for (int i = 1; i < cell.size(); i++) {
            row = row * 10 + (cell[i] - '0');
        }
        table[row][col] = value;
    }

    void resetCell(string cell) {
        int col = cell[0] - 'A';
        int row = 0;
        for (int i = 1; i < cell.size(); i++) {
            row = row * 10 + (cell[i] - '0');
        }
        table[row][col] = 0;
    }

    int getValue(string formula) {
        int i = 1;
        int a = 0;
        if (formula[i] >= 'A') {
            int col = formula[i] - 'A';
            int row = 0;
            i++;
            for (; i < formula.size(); i++) {
                if (formula[i] == '+') break;
                row = row * 10 + (formula[i] - '0');
            }
            a = table[row][col];
        } else {
            for (; i < formula.size(); i++) {
                if (formula[i] == '+') break;
                a = a * 10 + (formula[i] - '0');
            }
        }
        i++;
        int b = 0;
        if (formula[i] >= 'A') {
            int col = formula[i] - 'A';
            int row = 0;
            i++;
            for (; i < formula.size(); i++) {
                if (formula[i] == '=') break;
                row = row * 10 + (formula[i] - '0');
            }
            b = table[row][col];
        } else {
            for (; i < formula.size(); i++) {
                b = b * 10 + (formula[i] - '0');
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