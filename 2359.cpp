#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution {
   public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        while (node1 >= 0 || node2 >= 0) {
            if (node1 == node2) return node1;
            if (node1 >= 0) {
                int temp1 = node1;
                node1 = edges[node1];
                edges[temp1] = -2;
            }
            if (node2 >= 0) {
                int temp2 = node2;
                node2 = edges[node2];
                edges[temp2] = -3;
            }
            if (node1 >= 0 && edges[node1] == -3) {
                if (node2 >= 0 && edges[node2] == -2) {
                    return min(node1, node2);
                } else {
                    return node1;
                }
            }
            if (node2 >= 0 && edges[node2] == -2) {
                return node2;
            }
        }
        return -1;
    }
};

int main() {
    string problemName = "2359";
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
        auto edges = jread_vector(line_in);
        getline(file_in, line_in);
        auto node1 = jread_int(line_in);
        getline(file_in, line_in);
        auto node2 = jread_int(line_in);
        auto res = sol.closestMeetingNode(edges, node1, node2);
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