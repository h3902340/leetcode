#include <vector>
using namespace std;

// TODO: runtime is too bad (986 ms), try to optimize
struct Component {
    bool isCycle;
    int nodeCount;
};
class Solution {
   public:
    long long maxScore(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        vector<Component> comp;
        vector<int> compIndexes(n, -1);
        for (int i = 0; i < m; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int uIndex = compIndexes[u];
            int vIndex = compIndexes[v];
            if (uIndex == -1) {
                if (vIndex == -1) {
                    int compIndex = comp.size();
                    comp.push_back({false, 2});
                    compIndexes[u] = compIndex;
                    compIndexes[v] = compIndex;
                } else {
                    comp[vIndex].nodeCount++;
                    compIndexes[u] = vIndex;
                }
            } else {
                if (vIndex == -1) {
                    comp[uIndex].nodeCount++;
                    compIndexes[v] = uIndex;
                } else {
                    if (uIndex == vIndex) {
                        comp[uIndex].isCycle = true;
                    } else {
                        comp[uIndex].nodeCount += comp[vIndex].nodeCount;
                        for (int j = 0; j < n; j++) {
                            if (compIndexes[j] == vIndex) {
                                compIndexes[j] = uIndex;
                            }
                        }
                        comp[vIndex].nodeCount = 0;
                    }
                }
            }
        }
        sort(comp.begin(), comp.end(),
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
        for (int i = 0; i < comp.size(); i++) {
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