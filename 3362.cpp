#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 1e5;
const int MMAX = 1e5;
int prefix[NMAX + 1];
vector<int> arr[NMAX];
class Solution {
   public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int m = queries.size();
        for (int i = 0; i < n; i++) {
            prefix[i] = 0;
            arr[i].clear();
        }
        for (int i = 0; i < m; i++) {
            arr[queries[i][0]].push_back(queries[i][1]);
        }
        int res = m;
        int r = 0;
        priority_queue<int> pq;
        for (int j = 0; j < arr[r].size(); j++) {
            pq.push(arr[r][j]);
        }
        if (pq.size() < nums[0]) {
            return -1;
        }
        if (nums[0] > 0) {
            prefix[0] = nums[0];
            for (int j = 0; j < nums[0]; j++) {
                prefix[pq.top() + 1]--;
                pq.pop();
            }
            res -= nums[0];
        }
        for (int i = 1; i < n; i++) {
            r++;
            for (int j = 0; j < arr[r].size(); j++) {
                pq.push(arr[r][j]);
            }
            prefix[i] += prefix[i - 1];
            nums[i] -= prefix[i];
            if (nums[i] > 0) {
                prefix[i] += nums[i];
                for (int j = 0; j < nums[i]; j++) {
                    if (pq.empty()) {
                        return -1;
                    }
                    int t = pq.top();
                    if (t < i) {
                        return -1;
                    }
                    prefix[t + 1]--;
                    pq.pop();
                }
                res -= nums[i];
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3362";
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
        getline(file_in, line_in);
        auto queries = jread_vector2d(line_in);
        auto res = sol.maxRemoval(nums, queries);
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
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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