#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        if (m > n) {
            swap(nums1, nums2);
            swap(m, n);
        }
        if (m == 0) {
            int h = n >> 1;
            if (n & 1) {
                return nums2[h];
            }
            return (double)(nums2[h - 1] + nums2[h]) / 2;
        }
        int t = m + n;
        int h = (t >> 1) - 2;
        int l = -1;
        int r = m - 1;
        while (l <= r) {
            int a = (l + r) >> 1;
            int b = h - a;
            bool aOK = false;
            bool bOK = false;
            if (a == -1) {
                aOK = true;
                if (nums2[b] <= nums1[0]) {
                    bOK = true;
                }
            } else {
                if (b == -1) {
                    bOK = true;
                    if (nums1[a] <= nums2[0]) {
                        aOK = true;
                    }
                } else {
                    if (b + 1 == n || nums1[a] <= nums2[b + 1]) {
                        aOK = true;
                    }
                    if (a + 1 == m || nums2[b] <= nums1[a + 1]) {
                        bOK = true;
                    }
                }
            }
            if (aOK && bOK) {
                int right = 0;
                if (a + 1 == m) {
                    right = nums2[b + 1];
                } else if (b + 1 == n) {
                    right = nums1[a + 1];
                } else {
                    right = min(nums1[a + 1], nums2[b + 1]);
                }
                if (t & 1) {
                    return right;
                }
                int left = 0;
                if (a == -1) {
                    left = nums2[b];
                } else if (b == -1) {
                    left = nums1[a];
                } else {
                    left = max(nums1[a], nums2[b]);
                }
                return (double)(left + right) / 2;
            }
            if (aOK) {
                l = a + 1;
            } else {
                r = a - 1;
            }
        }
        return -1;
    }
};

int main() {
    string problemName = "4";
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
        auto res = sol.findMedianSortedArrays(nums1, nums2);
        getline(file_out, line_out);
        auto ans = jread_double(line_out);
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