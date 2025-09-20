#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Queue {
    int f;
    vector<int> arr;
};
#define ll long long
const int MEM = 1e5;
const int DES = 2e5;
const vector<int> EMPTY = {};
vector<int> mem[MEM];
Queue mp[DES + 1];

class Router {
   public:
    unordered_set<ll> exist;
    unordered_set<int> first;
    int i;
    int j;
    int n;
    int cnt;
    int t;
    Router(int memoryLimit) {
        i = 0;
        j = -1;
        n = memoryLimit;
        cnt = 0;
    }
    ll encode(int source, int destination) {
        return ((ll)source << 32) + destination;
    }
    void checkFirst(int destination) {
        if (!first.count(destination)) {
            mp[destination].f = 0;
            mp[destination].arr.clear();
            first.insert(destination);
        }
    }
    bool addPacket(int source, int destination, int timestamp) {
        checkFirst(destination);
        ll key = encode(source, destination);
        if (t == timestamp) {
            if (exist.count(key)) {
                return false;
            }
        } else {
            exist.clear();
            t = timestamp;
        }
        exist.insert(key);
        mp[destination].arr.push_back(timestamp);
        j++;
        if (j == n) {
            j = 0;
        }
        if (i == j) {
            forwardPacket();
        }
        mem[j] = {source, destination, timestamp};
        cnt++;
        return true;
    }

    vector<int> forwardPacket() {
        if (cnt == 0) {
            return EMPTY;
        }
        vector<int>& res = mem[i++];
        if (i == n) {
            i = 0;
        }
        mp[res[1]].f++;
        if (t == res[2]) {
            ll key = encode(res[0], res[1]);
            exist.erase(key);
        }
        cnt--;
        return res;
    }

    int getCount(int destination, int startTime, int endTime) {
        checkFirst(destination);
        auto& arr = mp[destination].arr;
        auto s = begin(arr) + mp[destination].f;
        auto e = end(arr);
        auto l = lower_bound(s, e, startTime);
        auto r = upper_bound(s, e, endTime);
        return distance(l, r);
    }
};

int main() {
    string problemName = "3508";
    auto begin = jtimer();
    vector<string> cmd = {"Router",        "addPacket", "addPacket",
                          "addPacket",     "addPacket", "addPacket",
                          "forwardPacket", "addPacket", "getCount"};
    int memoryLimit = 3;
    vector<vector<int>> add = {{},         {1, 4, 90},  {2, 5, 90},
                               {1, 4, 90}, {3, 5, 95},  {4, 5, 105},
                               {},         {5, 2, 110}, {}};
    vector<vector<int>> getCnt = {{}, {}, {}, {},           {},
                                  {}, {}, {}, {5, 100, 110}};
    vector<bool> addAns = {false, true,  true, false, true,
                           true,  false, true, false};
    vector<vector<int>> forwardAns = {{}, {},         {}, {}, {},
                                      {}, {2, 5, 90}, {}, {}};
    vector<int> getCntAns = {0, 0, 0, 0, 0, 0, 0, 0, 1};
    Router sol(memoryLimit);
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 1;
    int passCount = 0;
    for (int i = 0; i < cmd.size(); i++) {
        string& e = cmd[i];
        if (e == "Router") {
            continue;
        }
        if (e == "addPacket") {
            if (addAns[i] != sol.addPacket(add[i][0], add[i][1], add[i][2])) {
                allPass = false;
                printf("add wrong! i:%d\n", i);
                break;
            }
            continue;
        }
        if (e == "forwardPacket") {
            if (forwardAns[i] != sol.forwardPacket()) {
                allPass = false;
                printf("forward wrong! i:%d\n", i);
                break;
            }
            continue;
        }
        if (e == "getCount") {
            if (getCntAns[i] !=
                sol.getCount(getCnt[i][0], getCnt[i][1], getCnt[i][2])) {
                allPass = false;
                printf("getCnt wrong! i:%d\n", i);
                break;
            }
        }
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