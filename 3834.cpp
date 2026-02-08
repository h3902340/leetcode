#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int N = 1e5;
int nxt[N];
int pre[N];
class Solution {
   public:
    vector<long long> mergeAdjacent(vector<int>& nums) {
        int n = nums.size();
        vector<ll> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = nums[i];
            nxt[i] = i + 1;
            pre[i] = i - 1;
        }
        int i = 0;
        int len = n;
        while (i < n) {
            if (nxt[i] == n) {
                break;
            }
            if (res[i] == res[nxt[i]]) {
                res[i] = res[i] << 1;
                int j = nxt[nxt[i]];
                nxt[i] = j;
                if (j < n) {
                    pre[j] = i;
                }
                if (pre[i] >= 0) {
                    i = pre[i];
                }
            } else {
                i = nxt[i];
            }
        }
        i = 0;
        int j = 0;
        while (i < n) {
            res[j++] = res[i];
            i = nxt[i];
        }
        res.resize(j);
        return res;
    }
};

int main() {
    string problemName = "3834";
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
        auto res = sol.mergeAdjacent(nums);
        getline(file_out, line_out);
        auto ans = jread_vector_longlong(line_out);
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