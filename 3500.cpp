#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Line {
    long a;
    long b;
    Line(long a, long b) : a(a), b(b) {}
    Line() : a(0), b(0) {}
};
struct RationalPoint {
    long x;
    long y;
    long d;
    RationalPoint(long x, long y, long d) : x(x), y(y), d(d) {}
    RationalPoint() : x(0), y(0), d(0) {}
};
class Solution {
   public:
    long long minimumCost(vector<int>& nums, vector<int>& cost, int k) {
        int n = nums.size();
        for (int i = 1; i < n; i++) {
            nums[i] += nums[i - 1];
            cost[i] += cost[i - 1];
        }
        nums.insert(nums.begin(), 0);
        cost.insert(cost.begin(), 0);
        Line lines[1000];
        RationalPoint points[1000];
        int lineTop = -1;
        int pointTop = -1;
        long long ans = 0;
        for (int i = n; i >= 1; i--) {
            long a = -nums[i];
            long b = (long)nums[i] * cost[i] + ans + k * (cost[n] - cost[i]);
            if (lineTop == -1) {
                lines[0].a = a;
                lines[0].b = b;
                lineTop = 0;
            } else {
                if (pointTop != -1) {
                    RationalPoint p = points[pointTop];
                    while (a * p.x + b * p.d < p.y) {
                        pointTop--;
                        lineTop--;
                        if (pointTop == -1) break;
                        p = points[pointTop];
                    }
                }
                Line l = lines[lineTop];
                pointTop++;
                points[pointTop].x = l.b - b;
                points[pointTop].y = a * l.b - l.a * b;
                points[pointTop].d = a - l.a;
                lineTop++;
                lines[lineTop].a = a;
                lines[lineTop].b = b;
            }
            int l = 0;
            int r = pointTop;
            int x = cost[i - 1];
            int min = lineTop;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (points[mid].x < x * points[mid].d) {
                    r = mid - 1;
                    min = mid;
                } else {
                    l = mid + 1;
                }
            }
            ans = lines[min].a * x + lines[min].b;
        }
        return ans + k * cost[n];
    }
};

int main() {
    string problemName = "3500";
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
        auto cost = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        auto res = sol.minimumCost(nums, cost, k);
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