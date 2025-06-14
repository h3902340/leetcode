#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int C = 26;
int fre[C];
class Solution {
   public:
    int leastInterval(vector<char>& tasks, int n) {
        int t = tasks.size();
        for (int i = 0; i < C; i++) {
            fre[i] = 0;
        }
        for (auto& e : tasks) {
            fre[e - 'A']++;
        }
        int freMax = 0;
        for (int i = 0; i < C; i++) {
            if (freMax < fre[i]) {
                freMax = fre[i];
            }
        }
        int freMaxCount = 0;
        for (int i = 0; i < C; i++) {
            if (fre[i] == freMax) {
                freMaxCount++;
            }
        }
        // Idle only happens when there are not enough tasks to fill the gaps
        // formed by the tasks with the highest frequency.
        // For example, A..A..A --> AB.AB.A --> ABCABCA, if there is one D left,
        // we can adjust the schedule: A...A..A --> AB..AB.A --> ABC.ABCA -->
        // ABCDABCA
        // Idle case: A..A..A --> AB.AB.A --> ABCAB.A and there is no more task
        return max((freMax - 1) * (n + 1) + freMaxCount, t);
    }
};

int main() {
    string problemName = "621";
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
        auto tasks = jread_vector_char(line_in);
        getline(file_in, line_in);
        auto n = jread_int(line_in);
        auto res = sol.leastInterval(tasks, n);
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