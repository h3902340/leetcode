#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int v;
    int cnt;
};
const int N = 1e4;
Data st[N];
class StockSpanner {
   public:
    int r;
    StockSpanner() { r = -1; }

    int next(int price) {
        int res = 1;
        while (r >= 0 && st[r].v <= price) {
            res += st[r].cnt;
            r--;
        }
        st[++r] = {price, res};
        return res;
    }
};

int main() {
    string problemName = "901";
    auto begin = jtimer();
    StockSpanner sol;
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
        sol = StockSpanner();
        vector<int> res;
        res.push_back(-1);
        for (int i = 1; i < data.size(); i++) {
            res.push_back(sol.next(data[i][0]));
        }
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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