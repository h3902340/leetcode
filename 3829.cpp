#include <bitset>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int RIDER = 1000;
const int DRIVER = 1000;
bitset<RIDER + 1> riderBit;
class Queue {
    int q[RIDER];
    int l;
    int r;

   public:
    void push(int v) { q[r++] = v; }
    void pop() { l++; }
    int front() { return q[l]; }
    bool empty() { return l == r; }
    void clear() {
        l = 0;
        r = 0;
    }
};
Queue riders;
Queue drivers;

class RideSharingSystem {
    const vector<int> ERR = {-1, -1};

   public:
    RideSharingSystem() {
        riders.clear();
        drivers.clear();
    }

    void addRider(int riderId) {
        riders.push(riderId);
        riderBit.set(riderId, 1);
    }

    void addDriver(int driverId) { drivers.push(driverId); }

    vector<int> matchDriverWithRider() {
        if (drivers.empty()) {
            return ERR;
        }
        int d = drivers.front();
        while (!riders.empty()) {
            int r = riders.front();
            riders.pop();
            if (!riderBit.test(r)) {
                continue;
            }
            drivers.pop();
            return {d, r};
        }
        return ERR;
    }

    void cancelRider(int riderId) { riderBit.set(riderId, 0); }
};

int main() {
    string problemName = "3829";
    auto begin = jtimer();
    RideSharingSystem sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    vector<string> input = {"RideSharingSystem",
                            "addRider",
                            "addDriver",
                            "addRider",
                            "matchDriverWithRider",
                            "addDriver",
                            "cancelRider",
                            "matchDriverWithRider",
                            "matchDriverWithRider"};
    vector<vector<int>> param = {{}, {3}, {2}, {1}, {}, {5}, {3}, {}, {}};
    vector<vector<int>> ans = {{}, {}, {},     {},      {2, 3},
                               {}, {}, {5, 1}, {-1, -1}};
    vector<vector<int>> res;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == "addRider") {
            sol.addRider(param[i][0]);
            res.push_back({});
        } else if (input[i] == "addDriver") {
            sol.addDriver(param[i][0]);
            res.push_back({});
        } else if (input[i] == "matchDriverWithRider") {
            res.push_back(sol.matchDriverWithRider());
        } else if (input[i] == "cancelRider") {
            sol.cancelRider(param[i][0]);
            res.push_back({});
        } else {
            res.push_back({});
        }
    }
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
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}