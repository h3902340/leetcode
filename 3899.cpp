#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const double PI = 3.14159265358979323846;
class Solution {
   public:
    vector<double> internalAngles(vector<int>& sides) {
        sort(begin(sides), end(sides));
        if (sides[0] + sides[1] <= sides[2]) {
            return {};
        }
        double a = sides[0];
        double b = sides[1];
        double c = sides[2];
        vector<double> res(3);
        res[0] = acos((a * a + b * b - c * c) / (2 * a * b)) / PI * 180;
        res[1] = acos((a * a + c * c - b * b) / (2 * a * c)) / PI * 180;
        res[2] = acos((c * c + b * b - a * a) / (2 * c * b)) / PI * 180;
        sort(begin(res), end(res));
        return res;
    }
};

int main() {
    string problemName = "3899";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    const double tol = 1e-5;
    while (getline(file_in, line_in)) {
        auto sides = jread_vector(line_in);
        auto res = sol.internalAngles(sides);
        getline(file_out, line_out);
        auto ans = jread_vector_double(line_out);
        printf("Case %d", ++caseCount);
        if (vectorDoubleEqual(res, ans, tol)) {
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