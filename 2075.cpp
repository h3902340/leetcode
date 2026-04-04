#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    string decodeCiphertext(string encodedText, int rows) {
        int n = encodedText.size();
        int cols = n / rows;
        string res = "";
        int i = 0;
        int j = 0;
        while (i != 0 || j != cols) {
            res += encodedText[i * cols + j];
            i++;
            j++;
            if (i == rows || j == cols) {
                j = j - i + 1;
                i = 0;
            }
        }
        for (int k = res.size() - 1; k >= 0; k--) {
            if (res[k] == ' ') {
                res.pop_back();
            } else {
                break;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "2075";
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
        auto encodedText = jread_string(line_in);
        getline(file_in, line_in);
        auto rows = jread_int(line_in);
        auto res = sol.decodeCiphertext(encodedText, rows);
        getline(file_out, line_out);
        auto ans = jread_string(line_out);
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