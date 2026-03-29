#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Event {
    int i;
    int p;
    bool operator<(const Event& rhs) const {
        return p == rhs.p ? i > rhs.i : p < rhs.p;
    }
};
class EventManager {
   public:
    priority_queue<Event> pq;
    unordered_map<int, int> mp;
    EventManager(vector<vector<int>>& events) {
        for (auto& e : events) {
            pq.push({e[0], e[1]});
            mp[e[0]] = e[1];
        }
    }

    void updatePriority(int eventId, int newPriority) {
        pq.push({eventId, newPriority});
        mp[eventId] = newPriority;
    }

    int pollHighest() {
        while (!pq.empty()) {
            Event t = pq.top();
            pq.pop();
            if (mp[t.i] != t.p) {
                continue;
            }
            if (mp[t.i] == 0) {
                continue;
            }
            mp[t.i] = 0;
            return t.i;
        }
        return -1;
    }
};

int main() {
    string problemName = "3885";
    auto begin = jtimer();
    vector<vector<int>> events = {{5, 7}, {2, 7}, {9, 4}};
    EventManager sol(events);
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    vector<string> cmd = {"pollHighest", "updatePriority", "pollHighest",
                          "pollHighest"};
    vector<vector<int>> param = {{}, {9, 7}, {}, {}};
    vector<int> res(cmd.size());
    vector<int> ans = {2, -1, 5, 9};
    for (int i = 0; i < cmd.size(); i++) {
        if (cmd[i] == "pollHighest") {
            res[i] = sol.pollHighest();
        } else if (cmd[i] == "updatePriority") {
            sol.updatePriority(param[i][0], param[i][1]);
            res[i] = -1;
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