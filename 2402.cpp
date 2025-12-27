#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 100;
const int BIT_ID = 7;
const int MASK_ID = (1 << BIT_ID) - 1;
const auto cmp = [](vector<int>& a, vector<int>& b) { return a[0] < b[0]; };
int cnt[N];

class Solution {
   public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        int m = meetings.size();
        sort(meetings.begin(), meetings.end(), cmp);
        priority_queue<ll, vector<ll>, greater<ll>> used;
        priority_queue<int, vector<int>, greater<int>> free;
        for (int i = 0; i < n; i++) {
            free.push(i);
        }
        for (int i = 0; i < m; i++) {
            while (!used.empty()) {
                ll t = used.top();
                int id = t & MASK_ID;
                ll end = t >> BIT_ID;
                if (end > meetings[i][0]) {
                    break;
                }
                free.push(id);
                used.pop();
            }
            if (free.empty()) {
                ll t = used.top();
                used.pop();
                int id = t & MASK_ID;
                ll end = t >> BIT_ID;
                end += meetings[i][1] - meetings[i][0];
                cnt[id]++;
                used.push((end << BIT_ID) | id);
            } else {
                int id = free.top();
                free.pop();
                ll end = meetings[i][1];
                cnt[id]++;
                used.push((end << BIT_ID) | id);
            }
        }
        int res = 0;
        int best = 0;
        for (int i = 0; i < n; i++) {
            if (best < cnt[i]) {
                res = i;
                best = cnt[i];
            }
            cnt[i] = 0;
        }
        return res;
    }
};

int main() {
    string problemName = "2402";
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
        getline(file_in, line_in);
        auto meetings = jread_vector2d(line_in);
        auto res = sol.mostBooked(n, meetings);
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