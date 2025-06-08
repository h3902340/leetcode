#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int arr[N];
class Solution {
   public:
    int maxSumDistinctTriplet(vector<int>& x, vector<int>& y) {
        int n = x.size();
        unordered_map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int e = x[i];
            if (mp[e] < y[i]) {
                mp[e] = y[i];
            }
        }
        if (mp.size() < 3) {
            return -1;
        }
        int i = 0;
        for (auto& e : mp) {
            arr[i++] = e.second;
        }
        sort(begin(arr), begin(arr) + i, greater<int>());
        return arr[0] + arr[1] + arr[2];
    }
};

int main() {
    string problemName = "3572";
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
        auto x = jread_vector(line_in);
        getline(file_in, line_in);
        auto y = jread_vector(line_in);
        auto res = sol.maxSumDistinctTriplet(x, y);
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
        jprint_int(res, "res");
        jprint_int(ans, "ans");
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