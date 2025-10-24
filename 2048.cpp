#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 110;
const int arr[N]{1,      22,     122,    212,    221,    333,    1333,   3133,
                 3313,   3331,   4444,   14444,  22333,  23233,  23323,  23332,
                 32233,  32323,  32332,  33223,  33232,  33322,  41444,  44144,
                 44414,  44441,  55555,  122333, 123233, 123323, 123332, 132233,
                 132323, 132332, 133223, 133232, 133322, 155555, 212333, 213233,
                 213323, 213332, 221333, 223133, 223313, 223331, 224444, 231233,
                 231323, 231332, 232133, 232313, 232331, 233123, 233132, 233213,
                 233231, 233312, 233321, 242444, 244244, 244424, 244442, 312233,
                 312323, 312332, 313223, 313232, 313322, 321233, 321323, 321332,
                 322133, 322313, 322331, 323123, 323132, 323213, 323231, 323312,
                 323321, 331223, 331232, 331322, 332123, 332132, 332213, 332231,
                 332312, 332321, 333122, 333212, 333221, 422444, 424244, 424424,
                 424442, 442244, 442424, 442442, 444224, 444242, 444422, 515555,
                 551555, 555155, 555515, 555551, 666666, 1224444};
class Solution {
   public:
    int nextBeautifulNumber(int n) {
        int l = 0;
        int r = N - 1;
        int res = r;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (n < arr[mid]) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return arr[res];
    }
};

int main() {
    string problemName = "2048";
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
        auto res = sol.nextBeautifulNumber(n);
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