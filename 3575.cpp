#include <unordered_set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int MOD = 1e9 + 7;
const int N = 500;
const int D = 10;
const int MASK = 1 << D;
vector<int> adj[N];
int dp[MASK];
bool isGood[N];
int takenMask[N];
int dfsOrder[N];

class Solution {
   public:
    vector<int> val;
    vector<unordered_set<int>> digit;
    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        int n = vals.size();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for (int i = 0; i < n; i++) {
            if (par[i] != -1) {
                adj[par[i]].push_back(i);
            }
        }
        for (int i = 0; i < n; i++) {
            check(i, vals[i]);
        }
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int idx = 0;
            dfs(i, idx);
            sum += calc(idx + 1, vals);
            if (sum >= MOD) {
                sum -= MOD;
            }
        }
        return sum;
    }
    void dfs(int i, int& idx) {
        dfsOrder[idx] = i;
        for (auto e : adj[i]) {
            idx++;
            dfs(e, idx);
        }
    }
    int calc(int n, vector<int>& vals) {
        for (int j = 0; j < MASK; j++) {
            dp[j] = -1;
        }
        dp[0] = 0;
        for (int idx = 0; idx < n; idx++) {
            int i = dfsOrder[idx];
            if (!isGood[i]) continue;
            // this works like this: ...... --> ..A.... --> ..A..B..(A|B)... -->
            // ..A..B..C..(A|B)..(A|C)..(B|C)..(A|B|C)...
            for (int j = 0; j < MASK; j++) {
                if (dp[j] != -1 && !(j & takenMask[i])) {
                    int m = j | takenMask[i];
                    dp[m] = max(dp[m], dp[j] + vals[i]);
                }
            }
        }
        int res = 0;
        for (int j = 0; j < MASK; j++) {
            if (res < dp[j]) {
                res = dp[j];
            }
        }
        return res;
    }
    void check(int i, int a) {
        takenMask[i] = 0;
        while (a > 0) {
            int m = 1 << (a % 10);
            if (takenMask[i] & m) {
                isGood[i] = false;
                return;
            }
            takenMask[i] |= m;
            a /= 10;
        }
        isGood[i] = true;
    }
};

int main() {
    string problemName = "3575";
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
        auto vals = jread_vector(line_in);
        getline(file_in, line_in);
        auto par = jread_vector(line_in);
        auto res = sol.goodSubtreeSum(vals, par);
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