#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1000;
int q[N];

class Solution {
   public:
    int maxCandies(vector<int>& status, vector<int>& candies,
                   vector<vector<int>>& keys,
                   vector<vector<int>>& containedBoxes,
                   vector<int>& initialBoxes) {
        int l = 0;
        int r = 0;
        // status: 2: not seen, no key, 3: seen, no key, 4: not seen, has key,
        // 5: seen, has key
        for (auto e : initialBoxes) {
            if (status[e] == 1) {
                q[r++] = e;
                status[e] = 5;
            } else {
                status[e] = 3;
            }
        }
        for (auto& e : status) {
            if (e == 0) {
                e = 2;
            } else if (e == 1) {
                e = 4;
            }
        }
        int res = 0;
        while (l < r) {
            int f = q[l++];
            res += candies[f];
            for (auto e : keys[f]) {
                if (status[e] == 2) {
                    status[e] = 4;
                } else if (status[e] == 3) {
                    status[e] = 5;
                    q[r++] = e;
                }
            }
            for (auto e : containedBoxes[f]) {
                if (status[e] == 2) {
                    status[e] = 3;
                } else if (status[e] == 4) {
                    status[e] = 5;
                    q[r++] = e;
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1298";
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
        auto status = jread_vector(line_in);
        getline(file_in, line_in);
        auto candies = jread_vector(line_in);
        getline(file_in, line_in);
        auto keys = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto containedBoxes = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto initialBoxes = jread_vector(line_in);
        auto res =
            sol.maxCandies(status, candies, keys, containedBoxes, initialBoxes);
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