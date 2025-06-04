#include <set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int tmp[N];

class Solution {
   public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        multiset<int> lset;
        multiset<int> rset;
        for (int i = 0; i < n; i++) {
            tmp[i] = nums[i];
        }
        sort(nums.begin(), nums.begin() + k);
        int khalf = k >> 1;
        for (int i = 0; i < khalf; i++) {
            lset.insert(nums[i]);
        }
        for (int i = khalf; i < k; i++) {
            rset.insert(nums[i]);
        }
        vector<double> res(n - k + 1);
        bool isKeven = (k & 1) == 0;
        double med = *rset.begin();
        if (isKeven) {
            med = (*lset.rbegin() + med) / 2;
        }
        res[0] = med;
        for (int i = 0; i < n - k; i++) {
            int a = tmp[i];
            if (a < med) {
                auto it = lset.find(a);
                if (it != lset.end()) {
                    lset.erase(it);
                }
            } else {
                auto it = rset.find(a);
                if (it != rset.end()) {
                    rset.erase(it);
                }
            }
            int b = tmp[i + k];
            if (b < med) {
                lset.insert(b);
            } else {
                rset.insert(b);
            }
            if (lset.size() > khalf) {
                auto v = prev(lset.end());
                rset.insert(*v);
                lset.erase(v);
            } else if (lset.size() < khalf) {
                auto v = rset.begin();
                lset.insert(*v);
                rset.erase(v);
            }
            med = *rset.begin();
            if (isKeven) {
                med = (*lset.rbegin() + med) / 2;
            }
            res[i + 1] = med;
        }
        return res;
    }
};

int main() {
    string problemName = "480";
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
        auto k = jread_int(line_in);
        auto res = sol.medianSlidingWindow(nums, k);
        getline(file_out, line_out);
        auto ans = jread_vector_double(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_vector_double(res, "res");
        jprint_vector_double(ans, "ans");
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