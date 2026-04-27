#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class RangeModule {
   public:
    set<int> a;
    RangeModule() {}

    void addRange(int left, int right) {
        if (a.empty()) {
            a.insert(left);
            a.insert(right);
            return;
        }
        auto l = a.lower_bound(left);
        int x = distance(a.begin(), l);
        auto r = a.lower_bound(right + 1);
        int y = distance(r, a.end());
        a.erase(l, r);
        if (x % 2 == 0) {
            a.insert(left);
        }
        if (y % 2 == 0) {
            a.insert(right);
        }
    }

    bool queryRange(int left, int right) {
        if (a.empty()) {
            return false;
        }
        auto l = a.upper_bound(left);
        int x = distance(a.begin(), l);
        if (x % 2 == 0) {
            return false;
        }
        return *l >= right;
    }

    void removeRange(int left, int right) {
        if (a.empty()) {
            return;
        }
        auto l = a.lower_bound(left);
        int x = distance(a.begin(), l);
        auto r = a.lower_bound(right + 1);
        int y = distance(r, a.end());
        a.erase(l, r);
        if (x % 2 == 1) {
            a.insert(left);
        }
        if (y % 2 == 1) {
            a.insert(right);
        }
    }
};

int main() {
    string problemName = "715";
    auto begin = jtimer();
    RangeModule sol;
    vector<string> cmd = {"RangeModule", "addRange",   "removeRange",
                          "queryRange",  "queryRange", "queryRange"};
    vector<vector<int>> param = {{},       {10, 20}, {14, 16},
                                 {10, 14}, {13, 15}, {16, 17}};
    vector<string> ans = {"null", "null", "null", "true", "false", "true"};
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    printf("Case %d", ++caseCount);
    vector<string> res;
    for (int i = 0; i < cmd.size(); i++) {
        if (cmd[i] == "RangeModule") {
            res.push_back("null");
            continue;
        }
        if (cmd[i] == "addRange") {
            sol.addRange(param[i][0], param[i][1]);
            res.push_back("null");
        } else if (cmd[i] == "removeRange") {
            sol.removeRange(param[i][0], param[i][1]);
            res.push_back("null");
        } else if (cmd[i] == "queryRange") {
            bool a = sol.queryRange(param[i][0], param[i][1]);
            res.push_back(a ? "true" : "false");
        }
    }
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
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}