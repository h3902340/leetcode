#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int mp[N + 1];
class Solution {
   public:
    int minArrivalsToDiscard(vector<int>& arrivals, int w, int m) {
        int n = arrivals.size();
        int res = 0;
        int i = 0;
        int cnt = 0;
        for (auto& e : arrivals) {
            mp[e] = 0;
        }
        for (auto& e : arrivals) {
            mp[e]++;
            cnt++;
            if (cnt > w) {
                if (arrivals[i] > 0) {
                    mp[arrivals[i]]--;
                }
                i++;
            }
            if (mp[e] > m) {
                res++;
                mp[e]--;
                e = 0;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3679";
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
        auto arrivals = jread_vector(line_in);
        getline(file_in, line_in);
        auto w = jread_int(line_in);
        getline(file_in, line_in);
        auto m = jread_int(line_in);
        auto res = sol.minArrivalsToDiscard(arrivals, w, m);
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