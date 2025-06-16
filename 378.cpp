#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int res = 0;
        int l = matrix[0][0];
        int r = matrix[n - 1][n - 1];
        while (l <= r) {
            int mid = (l + r) >> 1;
            // "no greater" area on the Young tableau
            int c = 0;
            int i = n - 1;
            int j = 0;
            while (i >= 0 && j < n) {
                if (matrix[i][j] > mid) {
                    i--;
                } else {
                    c += i + 1;
                    j++;
                }
            }
            if (c < k) {
                l = mid + 1;
            } else {
                r = mid - 1;
                // the matrix might contain duplicates, but the wanted element
                // is always the smallest element which satisfies c>=k
                res = mid;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "378";
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
        auto matrix = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.kthSmallest(matrix, k);
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