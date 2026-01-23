#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Query {
    int i;
    int l;
    int r;
    int threshold;
    int b;
};
const int M = 5e4;
const int U = 1e9;
Query q[M];

class Solution {
   public:
    vector<int> subarrayMajority(vector<int>& nums,
                                 vector<vector<int>>& queries) {
        int n = nums.size();
        int m = queries.size();
        int bucket = sqrt((double)n);
        const auto cmp = [](Query& a, Query b) {
            if (a.b == b.b) {
                if (a.b & 1) {
                    return a.r > b.r;
                }
                return a.r < b.r;
            }
            return a.b < b.b;
        };
        for (int i = 0; i < m; i++) {
            q[i] = {i, queries[i][0], queries[i][1], queries[i][2],
                    queries[i][0] / bucket};
        }
        sort(begin(q), begin(q) + m, cmp);
        unordered_map<int, int> cnt;
        int mxC = 0;
        int mxV = U + 1;
        int l = 0;
        int r = -1;
        vector<int> res(m);
        for (int i = 0; i < m; i++) {
            while (l > q[i].l) {
                l--;
                cnt[nums[l]]++;
                if (mxC < cnt[nums[l]]) {
                    mxC = cnt[nums[l]];
                    mxV = nums[l];
                } else if (mxC == cnt[nums[l]]) {
                    mxV = min(mxV, nums[l]);
                }
            }
            while (r < q[i].r) {
                r++;
                cnt[nums[r]]++;
                if (mxC < cnt[nums[r]]) {
                    mxC = cnt[nums[r]];
                    mxV = nums[r];
                } else if (mxC == cnt[nums[r]]) {
                    mxV = min(mxV, nums[r]);
                }
            }
            while (l < q[i].l) {
                cnt[nums[l]]--;
                if (nums[l] == mxV) {
                    mxC--;
                    for (auto& e : cnt) {
                        if (mxC < e.second) {
                            mxC = e.second;
                            mxV = e.first;
                        } else if (mxC == e.second) {
                            mxV = min(mxV, e.first);
                        }
                    }
                }
                l++;
            }
            while (r > q[i].r) {
                cnt[nums[r]]--;
                if (nums[r] == mxV) {
                    mxC--;
                    for (auto& e : cnt) {
                        if (mxC < e.second) {
                            mxC = e.second;
                            mxV = e.first;
                        } else if (mxC == e.second) {
                            mxV = min(mxV, e.first);
                        }
                    }
                }
                r--;
            }
            if (mxC < q[i].threshold) {
                res[q[i].i] = -1;
            } else {
                res[q[i].i] = mxV;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3636";
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
        auto res = sol.subarrayMajority(nums, queries);
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