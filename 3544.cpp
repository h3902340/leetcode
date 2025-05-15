#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int NMAX = 5e4;
vector<int> adj[NMAX];
long long sums[NMAX];
long long mins[NMAX];
long long maxs[NMAX];
int parent[NMAX];
int levels[NMAX];

class Solution {
   public:
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums,
                                  int k) {
        int n = nums.size();
        int m = edges.size();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        levels[0] = 0;
        parent[0] = -1;
        bfs(0, 1);
        for (int l = n - 1; l >= 0; l--) {
            int node = levels[l];
            sums[node] = nums[node];
            for (auto& c : adj[node]) {
                sums[node] += sums[c];
            }
            mins[node] = -sums[node];
            maxs[node] = -sums[node];
        }
        for (int l = n - 1; l >= 0; l--) {
            int node = levels[l];
            long long max = nums[node];
            long long min = nums[node];
            for (auto& c : adj[node]) {
                max += maxs[c];
                min += mins[c];
            }
            if (maxs[node] < max) {
                maxs[node] = max;
            }
            if (mins[node] > min) {
                mins[node] = min;
            }
            int p = parent[node];
            for (int i = 1; i < k; i++) {
                if (p == -1) break;
                p = parent[p];
            }
            if (p != -1) {
                maxs[p] += sums[node] - mins[node];
                mins[p] += sums[node] - maxs[node];
            }
        }
        return maxs[0];
    }

   private:
    void bfs(int i, int j) {
        while (i < j) {
            int f = levels[i++];
            int p = parent[f];
            for (int k = adj[f].size() - 1; k >= 0; k--) {
                int c = adj[f][k];
                if (c == p) {
                    adj[f].erase(adj[f].begin() + k);
                    continue;
                }
                levels[j++] = c;
                parent[c] = f;
            }
        }
    }
};

int main() {
    string problemName = "3544";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in1;
    string line_in2;
    string line_in3;
    string line_out;
    while (getline(file_in, line_in1)) {
        auto edges = jread_vector2d(line_in1);
        getline(file_in, line_in2);
        auto nums = jread_vector(line_in2);
        getline(file_in, line_in3);
        int k = jread_int(line_in3);
        long long res = sol.subtreeInversionSum(edges, nums, k);
        getline(file_out, line_out);
        long long ans = jread_longlong(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        // printf("edges = %s\n", line_in1.c_str());
        // printf("nums = %s\n", line_in2.c_str());
        printf("k = %s\n", line_in3.c_str());
        printf("n = %zu\n", nums.size());
        jprint_longlong(res, "res");
        jprint_longlong(ans, "ans");
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