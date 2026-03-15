#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int minCost(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        unordered_map<int, int> mp1;
        unordered_map<int, int> mp2;
        for (int i = 0; i < n; i++) {
            mp1[nums1[i]]++;
            mp2[nums2[i]]++;
        }
        int d = 0;
        for (int i = 0; i < n; i++) {
            if ((mp1[nums1[i]] + mp2[nums1[i]]) % 2 == 1) {
                return -1;
            }
            d += abs(mp1[nums1[i]] - mp2[nums1[i]]);
            mp1[nums1[i]] = 0;
            mp2[nums1[i]] = 0;
            if ((mp1[nums2[i]] + mp2[nums2[i]]) % 2 == 1) {
                return -1;
            }
            d += abs(mp1[nums2[i]] - mp2[nums2[i]]);
            mp1[nums2[i]] = 0;
            mp2[nums2[i]] = 0;
        }
        return d >> 2;
    }
};

int main() {
    string problemName = "3868";
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
        auto nums1 = jread_vector(line_in);
        getline(file_in, line_in);
        auto nums2 = jread_vector(line_in);
        auto res = sol.minCost(nums1, nums2);
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