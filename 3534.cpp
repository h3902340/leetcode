#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Node {
    int i;
    int v;
};
const int N = 1e5;
const int LGN = 17;
int dp[N][LGN];
Node temp[N];
int labelToIndex[N];

class Solution {
   public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                     vector<vector<int>>& queries) {
        int m = queries.size();
        int lgn = log2(n) + 1;
        for (int i = 0; i < n; i++) {
            temp[i].i = i;
            temp[i].v = nums[i];
        }
        auto cmp = [](Node a, Node b) { return a.v < b.v; };
        sort(begin(temp), begin(temp) + n, cmp);
        int j = 1;
        for (int i = 0; i < n; i++) {
            Node a = temp[i];
            labelToIndex[a.i] = i;
            if (j < i + 1) {
                j = i + 1;
            }
            while (j < n) {
                Node b = temp[j];
                if (b.v - a.v > maxDiff) {
                    break;
                }
                j++;
            }
            dp[i][0] = j - 1;
        }
        for (int j = 1; j < lgn; j++) {
            for (int i = 0; i < n; i++) {
                int a = dp[i][j - 1];
                dp[i][j] = dp[a][j - 1];
            }
        }
        vector<int> res(m);
        for (int i = 0; i < m; i++) {
            int a = labelToIndex[queries[i][0]];
            int b = labelToIndex[queries[i][1]];
            if (a == b) {
                res[i] = 0;
                continue;
            }
            if (a > b) {
                swap(a, b);
            }
            if (dp[a][0] >= b) {
                res[i] = 1;
                continue;
            }
            res[i] = 0;
            while (a < b) {
                int l = 0;
                int r = lgn - 1;
                int max = -1;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (dp[a][mid] < b) {
                        l = mid + 1;
                        max = mid;
                    } else {
                        r = mid - 1;
                    }
                }
                if (max == -1) {
                    res[i]++;
                    break;
                }
                if (a == dp[a][max]) {
                    res[i] = -1;
                    break;
                }
                a = dp[a][max];
                res[i] += (1 << max);
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3534";
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
        auto nums = jread_vector(line_in);
        getline(file_in, line_in);
        auto maxDiff = jread_int(line_in);
        getline(file_in, line_in);
        auto queries = jread_vector2d(line_in);
        auto res = sol.pathExistenceQueries(n, nums, maxDiff, queries);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(n, "n");
        jprint(nums, "nums");
        jprint(maxDiff, "maxDiff");
        jprint(queries, "queries");
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