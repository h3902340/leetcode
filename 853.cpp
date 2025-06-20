#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
struct Car {
    int pos;
    int speed;
};
const int N = 1e5;
Car cars[N];
class Solution {
   public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        for (int i = 0; i < n; i++) {
            cars[i] = {position[i], speed[i]};
        }
        auto cmp = [](Car& a, Car& b) { return a.pos < b.pos; };
        sort(begin(cars), begin(cars) + n, cmp);
        int res = 1;
        int j = n - 1;
        for (int i = n - 2; i >= 0; i--) {
            if (!canReached(cars[i], cars[j], target)) {
                res++;
                j = i;
            }
        }
        return res;
    }
    bool canReached(Car& a, Car& b, int target) {
        return (ll)(target - b.pos) * a.speed >= (ll)(target - a.pos) * b.speed;
    }
};

int main() {
    string problemName = "853";
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
        auto target = jread_int(line_in);
        getline(file_in, line_in);
        auto position = jread_vector(line_in);
        getline(file_in, line_in);
        auto speed = jread_vector(line_in);
        auto res = sol.carFleet(target, position, speed);
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