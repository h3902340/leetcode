#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
const int U = 1e5;
int sparse[U + 1];
int dense[N];
int num;
void init() { num = 0; }
bool has(int x) {
    int idx = sparse[x];
    return (idx < num && dense[idx] == x);
}
void insert(int x) {
    int idx = sparse[x];
    if (idx >= num || dense[idx] != x) {
        sparse[x] = num;
        dense[num++] = x;
    }
}

class Solution {
   public:
    int minOperations(vector<int>& nums, vector<int>& target) {
        int n = nums.size();
        init();
        for (int i = 0; i < n; i++) {
            if (nums[i] != target[i]) {
                insert(nums[i]);
            }
        }
        return num;
    }
};

int main() {
    string problemName = "3810";
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
        auto target = jread_vector(line_in);
        auto res = sol.minOperations(nums, target);
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