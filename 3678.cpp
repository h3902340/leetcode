#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 101;
int arr[N];
class Solution {
   public:
    int smallestAbsent(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for (int i = 1; i < N; i++) {
            arr[i] = false;
        }
        for (auto& e : nums) {
            sum += e;
            if (e > 0) {
                arr[e] = true;
            }
        }
        int ave = (sum / n) + 1;
        if (ave < 1) {
            ave = 1;
        }
        for (int i = ave; i < N; i++) {
            if (!arr[i]) {
                return i;
            }
        }
        return N;
    }
};

int main() {
    string problemName = "3678";
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
        auto res = sol.smallestAbsent(nums);
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