#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 100;
vector<int> way(N + 1);
class Solution {
   public:
    vector<int> findCoins(vector<int>& numWays) {
        int n = numWays.size();
        for (int i = 1; i <= n; i++) {
            way[i] = 0;
        }
        way[0] = 1;
        vector<int> res;
        for (int i = 0; i < n; i++) {
            int coin = i + 1;
            if (numWays[i] == way[coin]) {
                continue;
            }
            if (numWays[i] < way[coin]) {
                return {};
            }
            if (numWays[i] > way[coin] + 1) {
                return {};
            }
            res.push_back(coin);
            for (int j = coin; j <= n; j++) {
                way[j] += way[j - coin];
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3592";
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
        auto numWays = jread_vector(line_in);
        auto res = sol.findCoins(numWays);
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