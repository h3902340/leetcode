#include <string>

#include "Jutilities.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

// TODO: use Berlekamp–Massey algo. instead
const int MOD = 1e9 + 7;
const int dim = 26;
using vec26 = array<int, dim>;
using matrix = array<vec26, dim>;
matrix I;
bool isInit = false;
static void init() {
    if (isInit) return;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            I[i][j] = 0;
        }
        I[i][i] = 1;
    }
    isInit = false;
}

class Solution {
   public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        init();
        int n = s.size();
        vec26 fre;
        for (int i = 0; i < dim; i++) {
            fre[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            fre[s[i] - 'a']++;
        }
        matrix a;
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                a[i][j] = 0;
            }
        }
        for (int i = 0; i < dim; i++) {
            for (int j = i + 1; j <= i + nums[i]; j++) {
                a[j % dim][i] = 1;
            }
        }
        matrix c = powMatrix(a, t, I);
        int res = 0;
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                res = (res + (long long)c[i][j] * fre[j]) % MOD;
            }
        }
        return res;
    }

   private:
    matrix powMatrix(matrix a, int b, matrix v) {
        if (b == 0) {
            return v;
        }
        if (b & 1) {
            return powMatrix(a, b - 1, mulMatrix(v, a));
        }
        return powMatrix(mulMatrix(a, a), b >> 1, v);
    }
    matrix mulMatrix(matrix a, matrix b) {
        matrix c;
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                c[i][j] = 0;
            }
        }
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (a[i][j] == 0) continue;
                for (int k = 0; k < dim; k++) {
                    c[i][k] = (c[i][k] + (long long)a[i][j] * b[j][k]) % MOD;
                }
            }
        }
        return c;
    }
};

int main() {
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/3337_in.txt");
    ifstream file_out("testcases/3337_out.txt");
    bool allPass = true;
    int caseIndex = 1;
    string line_in1;
    string line_in2;
    string line_in3;
    string line_out;
    while (getline(file_in, line_in1)) {
        string s = jread_string(line_in1);
        getline(file_in, line_in2);
        int t = jread_int(line_in2);
        getline(file_in, line_in3);
        vector<int> nums = jread_vector(line_in3);
        int res = sol.lengthAfterTransformations(s, t, nums);
        getline(file_out, line_out);
        int ans = jread_int(line_out);
        printf("Case %d", caseIndex++);
        if (res == ans) {
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        printf("s = %s\n", line_in1.c_str());
        printf("t = %s\n", line_in2.c_str());
        printf("nums = %s\n", line_in3.c_str());
        printf("res: %d, ans: %d\n", res, ans);
        printf("\n");
    }
    if (allPass) {
        printf("%sALL PASS\n%s", KGRN, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}