#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int BIT = 10;
const int CAP = 1 << BIT;
const int MIN_BIT = 6;
const int MASK = (1 << MIN_BIT) - 1;
vector<string> res[BIT + 1];
bool isInit = false;
void init() {
    res[0].push_back("0:00");
    for (int i = 1; i <= BIT; i++) {
        int a = (1 << i) - 1;
        while (a < CAP) {
            int h = a >> MIN_BIT;
            int m = a & MASK;
            if (h < 12 && m < 60) {
                string s = to_string(m);
                if (m < 10) {
                    s = '0' + s;
                }
                s = to_string(h) + ':' + s;
                res[i].push_back(s);
            }
            int r = a & -a;
            int n = a + r;
            a = ((n ^ a) >> 2) / r | n;
        }
    }
}

class Solution {
   public:
    vector<string> readBinaryWatch(int turnedOn) {
        if (!isInit) {
            init();
            isInit = true;
        }
        return res[turnedOn];
    }
};

int main() {
    string problemName = "401";
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
        auto turnedOn = jread_int(line_in);
        auto res = sol.readBinaryWatch(turnedOn);
        getline(file_out, line_out);
        auto ans = jread_vector_string(line_out);
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