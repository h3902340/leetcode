#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    long long totalScore(int hp, vector<int>& damage,
                         vector<int>& requirement) {
        int n = damage.size();
        ll res = 0;
        if (hp - damage[0] >= requirement[0]) {
            res++;
        }
        for (int i = 1; i < n; i++) {
            damage[i] += damage[i - 1];
            int l = 0;
            int r = i;
            int left = i + 1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                int d = damage[i];
                if (mid > 0) {
                    d -= damage[mid - 1];
                }
                if (hp - d < requirement[i]) {
                    l = mid + 1;
                } else {
                    left = mid;
                    r = mid - 1;
                }
            }
            res += i - left + 1;
        }
        return res;
    }
};

int main() {
    string problemName = "3771";
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
        auto hp = jread_int(line_in);
        getline(file_in, line_in);
        auto damage = jread_vector(line_in);
        getline(file_in, line_in);
        auto requirement = jread_vector(line_in);
        auto res = sol.totalScore(hp, damage, requirement);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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