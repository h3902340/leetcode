#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e5;
int indices[N];

class Solution {
   public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        int m = queries.size();
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            int e = nums[i];
            mp[e].push_back(i);
            indices[i] = mp[e].size() - 1;
        }
        vector<int> res(m);
        for (int i = 0; i < m; i++) {
            int e = queries[i];
            int a = nums[e];
            int index = indices[e];
            int size = mp[a].size();
            if (size == 1) {
                res[i] = -1;
            } else {
                vector<int>& arr = mp[a];
                int a = arr[(index + 1) % size];
                int b = arr[index];
                int c = a - b;
                if (a < b) {
                    c += n;
                }
                int a2 = arr[index];
                int b2 = arr[(index - 1 + size) % size];
                int c2 = a2 - b2;
                if (a2 < b2) {
                    c2 += n;
                }
                res[i] = min(c, c2);
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3488";
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
        auto queries = jread_vector(line_in);
        auto res = sol.solveQueries(nums, queries);
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
        jprint_vector(nums, "nums");
        jprint_vector(queries, "queries");
        jprint_vector(res, "res");
        jprint_vector(ans, "ans");
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