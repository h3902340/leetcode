#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int D = 9;
int subtreeSize[D + 1];
bool isInit = false;
static void init() {
    if (isInit) return;
    subtreeSize[0] = 0;
    for (int i = 1; i <= D; i++) {
        subtreeSize[i] = subtreeSize[i - 1] * 10 + 1;
    }
    isInit = true;
}
const int N = 1e9;

class Solution {
   public:
    int findKthNumber(int n, int k) {
        init();
        int d = 0;
        int a = n;
        int b = 1;
        while (a > 0) {
            a /= 10;
            b *= 10;
            d++;
        }
        b /= 10;
        d--;
        int res = 0;
        int i = 1;
        int len = n - b + 1;
        int nxtlen = 0;
        while (k > 0) {
            for (; i < 10; i++) {
                int tree = subtreeSize[d];
                if (len > b) {
                    tree += b;
                    len -= b;
                    nxtlen = b;
                } else {
                    tree += len;
                    nxtlen = len;
                    len = 0;
                }
                if (k <= tree) {
                    break;
                }
                k -= tree;
            }
            res = res * 10 + i;
            k--;
            len = nxtlen;
            i = 0;
            b /= 10;
            d--;
        }
        return res;
    }
};

int main() {
    string problemName = "440";
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
        auto n = jread_int(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.findKthNumber(n, k);
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
        jprint_int(n, "n");
        jprint_int(k, "k");
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