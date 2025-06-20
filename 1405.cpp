#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    char c;
    int cnt;
};
class Solution {
   public:
    string longestDiverseString(int a, int b, int c) {
        Data arr[3]{{'a', a}, {'b', b}, {'c', c}};
        auto cmp = [](Data& a, Data& b) { return a.cnt > b.cnt; };
        sort(begin(arr), begin(arr) + 3, cmp);
        int n = a + b + c;
        string res = "";
        while (true) {
            if (arr[1].cnt == 0) {
                for (int j = 0; j < min(2, arr[0].cnt); j++) {
                    res += arr[0].c;
                }
                break;
            }
            if (arr[0].cnt > arr[1].cnt) {
                res += arr[0].c;
                arr[0].cnt--;
            }
            res += arr[0].c;
            res += arr[1].c;
            arr[0].cnt--;
            arr[1].cnt--;
            sort(begin(arr), begin(arr) + 3, cmp);
        }
        return res;
    }
};

int main() {
    string problemName = "1405";
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
        auto a = jread_int(line_in);
        getline(file_in, line_in);
        auto b = jread_int(line_in);
        getline(file_in, line_in);
        auto c = jread_int(line_in);
        auto res = sol.longestDiverseString(a, b, c);
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