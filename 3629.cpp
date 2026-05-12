#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
const int U = 1e6;
struct Data {
    int i;
    int d;
};
bool isInit = false;
bool prime[U + 1];
void init() {
    memset(prime, 1, sizeof(prime));
    prime[0] = 0;
    prime[1] = 0;
    for (int i = 2; i * i <= U; i++) {
        if (prime[i]) {
            for (int j = i * 2; j <= U; j += i) {
                prime[j] = 0;
            }
        }
    }
}
Data q[N];
bool vis[N];
bool check[U + 1];
vector<int> has[U + 1];
class Solution {
   public:
    int minJumps(vector<int>& nums) {
        if (!isInit) {
            init();
            isInit = true;
        }
        int n = nums.size();
        if (n == 1) {
            return 0;
        }
        int mx = 0;
        for (int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);
            vis[i] = 0;
        }
        for (int i = 0; i <= mx; i++) {
            has[i].clear();
            check[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            has[nums[i]].push_back(i);
        }
        q[0] = {0, 0};
        vis[0] = 1;
        int l = 0;
        int r = 1;
        while (l < r) {
            Data u = q[l++];
            int p = nums[u.i];
            if (prime[p] && !check[p]) {
                for (int i = p; i <= mx; i += p) {
                    for (auto& h : has[i]) {
                        if (h == n - 1) {
                            return u.d + 1;
                        }
                        if (vis[h]) {
                            continue;
                        }
                        q[r++] = {h, u.d + 1};
                        vis[h] = 1;
                    }
                }
                check[p] = 1;
            }
            if (u.i > 0) {
                if (!vis[u.i - 1]) {
                    q[r++] = {u.i - 1, u.d + 1};
                    vis[u.i - 1] = 1;
                }
            }
            if (u.i + 1 < n) {
                if (u.i + 1 == n - 1) {
                    return u.d + 1;
                }
                if (!vis[u.i + 1]) {
                    q[r++] = {u.i + 1, u.d + 1};
                    vis[u.i + 1] = 1;
                }
            }
        }
        return -1;
    }
};

int main() {
    string problemName = "3629";
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
        auto res = sol.minJumps(nums);
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