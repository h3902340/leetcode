#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Frac {
    int x;
    int y;
    double delta;
};

class Solution {
   public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        int n = classes.size();
        double res = 0;
        auto cmp = [](Frac& a, Frac& b) { return a.delta < b.delta; };
        priority_queue<Frac, vector<Frac>, decltype(cmp)> pq(cmp);
        for (auto& c : classes) {
            pq.push({c[0], c[1], calcDelta(c[0], c[1])});
            res += (double)c[0] / c[1];
        }
        for (int i = 0; i < extraStudents; i++) {
            Frac t = pq.top();
            pq.pop();
            res += t.delta;
            t.x++;
            t.y++;
            t.delta = calcDelta(t.x, t.y);
            pq.push(t);
        }
        res /= n;
        return res;
    }
    double calcDelta(int x, int y) {
        return (double)(x + 1) / (y + 1) - (double)x / y;
    }
};

int main() {
    string problemName = "1792";
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
        auto classes = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto extraStudents = jread_int(line_in);
        auto res = sol.maxAverageRatio(classes, extraStudents);
        getline(file_out, line_out);
        auto ans = jread_double(line_out);
        printf("Case %d", ++caseCount);
        if (abs(res - ans) < 0.00001) {
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