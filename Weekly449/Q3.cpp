#include <vector>
using namespace std;

struct Component {
    bool isCycle;
    int nodeCount;
};
const int NMAX = 50000;
int parents[NMAX];
vector<Component> comp(NMAX);
class Solution {
   public:
    long long maxScore(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        for (int i = 0; i < n; i++) {
            parents[i] = -NMAX - 1;
        }
        int index = 0;
        for (int i = 0; i < m; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int uParent = getParent(u);
            int vParent = getParent(v);
            int uCompIndex = -parents[uParent] - 1;
            int vCompIndex = -parents[vParent] - 1;
            if (uCompIndex == NMAX) {
                if (vCompIndex == NMAX) {
                    comp[index].isCycle = false;
                    comp[index].nodeCount = 2;
                    parents[uParent] = -(++index);
                    parents[vParent] = uParent;
                } else {
                    comp[vCompIndex].nodeCount++;
                    parents[uParent] = vParent;
                }
            } else {
                if (vCompIndex == NMAX) {
                    comp[uCompIndex].nodeCount++;
                    parents[vParent] = uParent;
                } else {
                    if (uCompIndex == vCompIndex) {
                        comp[uCompIndex].isCycle = true;
                    } else {
                        comp[uCompIndex].nodeCount +=
                            comp[vCompIndex].nodeCount;
                        comp[vCompIndex].nodeCount = 0;
                        parents[vParent] = uParent;
                    }
                }
            }
        }
        sort(comp.begin(), comp.begin() + index,
             [](const Component& a, const Component& b) {
                 if (a.isCycle) {
                     if (b.isCycle) {
                         return a.nodeCount > b.nodeCount;
                     } else {
                         return true;
                     }
                 } else {
                     if (b.isCycle) {
                         return false;
                     } else {
                         return a.nodeCount > b.nodeCount;
                     }
                 }
             });
        long long ans = 0;
        int curr = n;
        for (int i = 0; i < index; i++) {
            if (comp[i].nodeCount == 0) continue;
            int left = curr;
            int right = curr;
            curr--;
            for (int j = 1; j < comp[i].nodeCount; j++) {
                ans += (long long)left * curr;
                left = curr;
                curr--;
                j++;
                if (j < comp[i].nodeCount) {
                    ans += (long long)right * curr;
                    right = curr;
                    curr--;
                } else {
                    break;
                }
            }
            if (comp[i].isCycle) {
                ans += (long long)left * right;
            }
        }
        return ans;
    }

   private:
    int getParent(int node) {
        int p = parents[node];
        if (p < 0) {
            return node;
        }
        return getParent(p);
    }
};

// 130
int n = 7;
vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5}, {5, 6}};

// 82
/* int n = 6;
vector<vector<int>> edges = {{0, 3}, {4, 5}, {2, 0}, {1, 3}, {2, 4}, {1, 5}}; */

int main() {
    Solution sol;
    long long ans = sol.maxScore(n, edges);
    printf("ans = %lld\n", ans);
    return 0;
}