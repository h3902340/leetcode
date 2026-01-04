#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
const int N_SQRT = 317;
const int N_CUBIC = 47;
bool isInit = false;
int cnt[N + 1];
int d[N + 1];
void init() {
    for (int i = 2; i <= N; i++) {
        d[i] += 1 + i;
        if (cnt[i] == 0) {
            for (int j = i; j <= N; j += i) {
                if (i < N_SQRT) {
                    int a = i * i;
                    if (j % a == 0) {
                        cnt[j] = 3;
                        continue;
                    }
                }
                cnt[j]++;
                d[j] += i;
            }
            if (i < N_CUBIC) {
                int a = i * i;
                int b = a * i;
                d[b] += i + a;
                cnt[b] = 2;
            }
        }
    }
}

class Solution {
   public:
    int sumFourDivisors(vector<int>& nums) {
        int n = nums.size();
        if (!isInit) {
            init();
            isInit = true;
        }
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (cnt[nums[i]] == 2) {
                res += d[nums[i]];
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1390";
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
        auto res = sol.sumFourDivisors(nums);
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