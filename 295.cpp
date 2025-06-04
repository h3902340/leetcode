#include <set>
#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NUMMAX = 1e5;

class MedianFinder {
   public:
    priority_queue<int> l;
    priority_queue<int, vector<int>, greater<int>> r;
    double med;
    int cnt;
    MedianFinder() {
        med = NUMMAX + 1;
        cnt = 0;
    }

    void addNum(int num) {
        if (med == NUMMAX + 1) {
            r.push(num);
        } else {
            if (num < med) {
                l.push(num);
            } else {
                r.push(num);
            }
            if (l.size() > r.size()) {
                auto v = l.top();
                l.pop();
                r.push(v);
            } else if (l.size() + 1 < r.size()) {
                auto v = r.top();
                r.pop();
                l.push(v);
            }
        }
        cnt++;
        med = r.top();
        if ((cnt & 1) == 0) {
            med = (l.top() + med) / 2;
        }
    }

    double findMedian() { return med; }
};

int main() {
    string problemName = "295";
    auto begin = jtimer();
    MedianFinder sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    while (getline(file_in, line_in)) {
        auto cmds = jread_vector_string(line_in);
        getline(file_in, line_in);
        auto data = jread_vector2d(line_in);
        vector<double> res;
        for (int i = 0; i < cmds.size(); i++) {
            if (cmds[i] == "MedianFinder") {
                sol = MedianFinder();
                res.push_back(NUMMAX + 1);
            } else if (cmds[i] == "addNum") {
                sol.addNum(data[i][0]);
                res.push_back(NUMMAX + 1);
            } else if (cmds[i] == "findMedian") {
                res.push_back(sol.findMedian());
            }
        }
        getline(file_out, line_out);
        auto ans = jread_vector_double(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_vector_string(cmds, "cmds");
        jprint_vector_double(res, "res");
        jprint_vector_double(ans, "ans");
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