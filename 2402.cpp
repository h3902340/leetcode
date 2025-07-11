#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
struct Room {
    int i;
    ll end;
};
class Solution {
   public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        int m = meetings.size();
        auto cmp = [](vector<int>& a, vector<int>& b) { return a[0] < b[0]; };
        sort(meetings.begin(), meetings.end(), cmp);
        vector<int> cnt(n);
        vector<Room> tmp(n);
        auto cmp2 = [](Room& a, Room& b) {
            if (a.end == b.end) {
                return a.i > b.i;
            }
            return a.end > b.end;
        };
        priority_queue<Room, vector<Room>, decltype(cmp2)> pq(cmp2);
        for (int i = 0; i < n; i++) {
            pq.push({i, 0});
        }
        for (int i = 0; i < m; i++) {
            int index = n;
            int j = 0;
            while (!pq.empty() && pq.top().end <= meetings[i][0]) {
                Room t = pq.top();
                tmp[j++] = t;
                if (index > t.i) {
                    index = t.i;
                }
                pq.pop();
            }
            if (index == n) {
                Room t = pq.top();
                tmp[j++] = t;
                pq.pop();
                index = t.i;
                ll end = t.end;
                while (!pq.empty() && pq.top().end == end) {
                    t = pq.top();
                    tmp[j++] = t;
                    if (index > t.i) {
                        index = t.i;
                    }
                    pq.pop();
                }
            }
            for (int k = 0; k < j; k++) {
                if (tmp[k].i == index) {
                    if (tmp[k].end > meetings[i][0]) {
                        tmp[k].end += meetings[i][1] - meetings[i][0];
                    } else {
                        tmp[k].end = meetings[i][1];
                    }
                    cnt[tmp[k].i]++;
                }
                pq.push(tmp[k]);
            }
        }
        int res = 0;
        int best = cnt[0];
        for (int i = 1; i < n; i++) {
            if (best < cnt[i]) {
                res = i;
                best = cnt[i];
            }
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