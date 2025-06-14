#include <map>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        int n = barcodes.size();
        for (int i = 0; i < n; i++) {
            int j = i + 1;
            while (j < n && barcodes[i] == barcodes[j]) {
                j++;
            }
            if (j < n) {
                swap(barcodes[i + 1], barcodes[j]);
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            int j = i - 1;
            while (j >= 0 && barcodes[i] == barcodes[j]) {
                j--;
            }
            if (j >= 0) {
                swap(barcodes[i - 1], barcodes[j]);
            }
        }
        return barcodes;
    }
};

int main() {
    string problemName = "1054";
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
        auto barcodes = jread_vector(line_in);
        auto res = sol.rearrangeBarcodes(barcodes);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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