#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int M = 100;
int prefix[M];
unordered_map<int, int> freq;

class Solution {
   public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 1; j < n; j++) {
                matrix[i][j] += matrix[i][j - 1];
            }
        }
        int res = 0;
        for (int i1 = -1; i1 < n; i1++) {
            for (int i2 = i1 + 1; i2 < n; i2++) {
                res += subarraySum(matrix, i1, i2, target);
            }
        }
        return res;
    }
    int subarraySum(vector<vector<int>>& matrix, int i1, int i2, int target) {
        int m = matrix.size();
        freq.clear();
        int sum = matrix[0][i2];
        if (i1 != -1) {
            sum -= matrix[0][i1];
        }
        freq[sum]++;
        prefix[0] = sum;
        for (int i = 1; i < m; i++) {
            sum += matrix[i][i2];
            if (i1 != -1) {
                sum -= matrix[i][i1];
            }
            freq[sum]++;
            prefix[i] = sum;
        }
        int res = freq[target];
        if (target == 0) {
            for (auto f : freq) {
                res += f.second * (f.second - 1) >> 1;
            }
        } else {
            for (int i = 0; i < m; i++) {
                int right = prefix[i] + target;
                res += freq[right];
                freq[prefix[i]]--;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1074";
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
        auto target = jread_int(line_in);
        auto res = sol.numSubmatrixSumTarget(matrix, target);
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