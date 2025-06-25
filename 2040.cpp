#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
class Solution {
   public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2,
                                 long long k) {
        int m = nums1.size();
        int n = nums2.size();
        int negIndex1 = -1;
        int negIndex2 = -1;
        for (int i = 0; i < m; i++) {
            if (nums1[i] < 0) {
                negIndex1 = i;
            } else {
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums2[i] < 0) {
                negIndex2 = i;
            } else {
                break;
            }
        }
        ll negCnt = (ll)(negIndex1 + 1) * (n - negIndex2 - 1) +
                    (ll)(negIndex2 + 1) * (m - negIndex1 - 1);
        if (negCnt < k) {
            k -= negCnt;
            ll l = -1;
            if (negIndex1 != -1 && negIndex2 != -1) {
                l = (ll)nums1[negIndex1] * nums2[negIndex2];
            }
            if (negIndex1 + 1 < m && negIndex2 + 1 < n) {
                if (l == -1) {
                    l = (ll)nums1[negIndex1 + 1] * nums2[negIndex2 + 1];
                } else {
                    l = min(l, (ll)nums1[negIndex1 + 1] * nums2[negIndex2 + 1]);
                }
            }
            ll r =
                max((ll)nums1[0] * nums2[0], (ll)nums1[m - 1] * nums2[n - 1]);
            while (l <= r) {
                ll mid = (l + r) >> 1;
                ll cnt = 0;
                int i = 0;
                int j = negIndex2;
                while (j >= 0 && i <= negIndex1) {
                    if ((ll)nums1[i] * nums2[j] <= mid) {
                        cnt += negIndex1 - i + 1;
                        j--;
                    } else {
                        i++;
                    }
                }
                i = negIndex1 + 1;
                j = n - 1;
                while (j > negIndex2 && i < m) {
                    if ((ll)nums1[i] * nums2[j] <= mid) {
                        cnt += j - negIndex2;
                        i++;
                    } else {
                        j--;
                    }
                }
                if (cnt < k) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            return l;
        }
        ll l = min((ll)nums1[0] * nums2[n - 1], (ll)nums2[0] * nums1[m - 1]);
        ll r = 0;
        if (negIndex1 != -1 && negIndex2 + 1 < n) {
            r = (ll)nums1[negIndex1] * nums2[negIndex2 + 1];
        }
        if (negIndex2 != -1 && negIndex1 + 1 < m) {
            if (r == 0) {
                r = (ll)nums2[negIndex2] * nums1[negIndex1 + 1];
            } else {
                r = max(r, (ll)nums2[negIndex2] * nums1[negIndex1 + 1]);
            }
        }
        while (l <= r) {
            ll mid = (l + r) >> 1;
            ll cnt = 0;
            int i = negIndex1;
            int j = n - 1;
            while (j >= negIndex2 + 1 && i >= 0) {
                if ((ll)nums1[i] * nums2[j] <= mid) {
                    cnt += i + 1;
                    j--;
                } else {
                    i--;
                }
            }
            i = m - 1;
            j = negIndex2;
            while (j >= 0 && i >= negIndex1 + 1) {
                if ((ll)nums1[i] * nums2[j] <= mid) {
                    cnt += j + 1;
                    i--;
                } else {
                    j--;
                }
            }
            if (cnt < k) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return l;
    }
};

int main() {
    string problemName = "2040";
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
        getline(file_in, line_in);
        auto k = jread_longlong(line_in);
        auto res = sol.kthSmallestProduct(nums1, nums2, k);
        getline(file_out, line_out);
        auto ans = jread_longlong(line_out);
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