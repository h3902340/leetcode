#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minMoves(int sx, int sy, int tx, int ty) {
        if (sx == tx && sy == ty) {
            return 0;
        }
        if (sx > tx || sy > ty) {
            return -1;
        }
        int res = 1;
        if (tx > ty) {
            if (tx > (ty << 1)) {
                if (tx & 1) {
                    return -1;
                }
                tx >>= 1;
            } else {
                tx -= ty;
            }
            int a = minMoves(sx, sy, tx, ty);
            if (a == -1) {
                return -1;
            }
            res += a;
        } else if (ty > tx) {
            if (ty > (tx << 1)) {
                if (ty & 1) {
                    return -1;
                }
                ty >>= 1;
            } else {
                ty -= tx;
            }
            int a = minMoves(sx, sy, tx, ty);
            if (a == -1) {
                return -1;
            }
            res += a;
        } else {
            int a = minMoves(sx, sy, 0, ty);
            int b = minMoves(sx, sy, tx, 0);
            if (a == -1) {
                if (b == -1) {
                    return -1;
                } else {
                    res += b;
                }
            } else {
                if (b == -1) {
                    res += a;
                } else {
                    res += min(a, b);
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3609";
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
        auto sx = jread_int(line_in);
        getline(file_in, line_in);
        auto sy = jread_int(line_in);
        getline(file_in, line_in);
        auto tx = jread_int(line_in);
        getline(file_in, line_in);
        auto ty = jread_int(line_in);
        auto res = sol.minMoves(sx, sy, tx, ty);
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