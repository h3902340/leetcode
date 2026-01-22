#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
#define pa pair<ll, int>
const int N = 1e5;
int l[N];
int r[N];
ll s[N];

class Solution {
   public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        priority_queue<pa, vector<pa>, greater<pa>> pq;
        int bad = 0;
        for (int i = 0; i < n; i++) {
            l[i] = i - 1;
            r[i] = i + 1;
            s[i] = nums[i];
            if (i + 1 < n) {
                pq.emplace(nums[i] + nums[i + 1], i);
                if (nums[i] > nums[i + 1]) {
                    bad++;
                }
            }
        }
        int res = 0;
        while (bad > 0) {
            if (pq.empty()) {
                break;
            }
            pa t = pq.top();
            pq.pop();
            if (r[t.second] == n) {
                continue;
            }
            if (s[t.second] + s[r[t.second]] != t.first) {
                continue;
            }
            res++;
            ll tmp = s[t.second];
            s[t.second] = t.first;
            int nxt = r[r[t.second]];
            if (nxt < n) {
                pq.emplace(s[t.second] + s[nxt], t.second);
                if (s[r[t.second]] > s[nxt]) {
                    if (s[t.second] <= s[nxt]) {
                        bad--;
                    }
                } else {
                    if (s[t.second] > s[nxt]) {
                        bad++;
                    }
                }
                l[nxt] = t.second;
            }
            int pre = l[t.second];
            if (pre >= 0) {
                pq.emplace(s[pre] + s[t.second], pre);
                if (s[pre] > tmp) {
                    if (s[pre] <= s[t.second]) {
                        bad--;
                    }
                } else {
                    if (s[pre] > s[t.second]) {
                        bad++;
                    }
                }
            }
            if (tmp > s[r[t.second]]) {
                bad--;
            }
            r[r[t.second]] = n;
            l[r[t.second]] = -1;
            r[t.second] = nxt;
        }
        return res;
    }
};

int main() {
    string problemName = "3507";
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
        auto nums = jread_vector(line_in);
        auto res = sol.minimumPairRemoval(nums);
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