#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1,
                                    vector<vector<int>>& nums2) {
        vector<vector<int>> res;
        int m = nums1.size();
        int n = nums2.size();
        int i = 0;
        int j = 0;
        while (i < m && j < n) {
            if (nums1[i][0] < nums2[j][0]) {
                res.push_back(nums1[i]);
                i++;
            } else if (nums1[i][0] == nums2[j][0]) {
                res.push_back({nums1[i][0], nums1[i][1] + nums2[j][1]});
                i++;
                j++;
            } else {
                res.push_back(nums2[j]);
                j++;
            }
        }
        while (i < m) {
            res.push_back(nums1[i]);
            i++;
        }
        while (j < n) {
            res.push_back(nums2[j]);
            j++;
        }
        return res;
    }
};

int main() {
    string problemName = "2570";
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
        auto nums1 = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto nums2 = jread_vector2d(line_in);
        auto res = sol.mergeArrays(nums1, nums2);
        getline(file_out, line_out);
        auto ans = jread_vector2d(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_vector2d(res, "res");
        jprint_vector2d(ans, "ans");
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