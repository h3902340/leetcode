#include <vector>
using namespace std;

// the problem is wrongly set, even the offical testcases are wrong, not optimal
// this greedy method is wrong, counterexample: n = 10, edges =
// [[0,1],[1,2],[3,4],[4,5]], greedy will give: 9 - 10 - 8 and 5 - 7 - 6 with
// result 247 but the answer is: 8 - 10- 7 and 6 - 9 - 5 with result 249
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

int m = 0;
const int size = 10;
const int size_half = size >> 1;
int labels[size];
static void perm(int labels[size], int i) {
    if (i == size) {
        int ans = 0;
        for (int j = 0; j < size_half; j++) {
            ans += labels[j] * labels[(j + 1) % size_half];
        }
        for (int j = size_half; j < size; j++) {
            ans += labels[j] * labels[(j + 1) % size_half + size_half];
        }
        if (ans > m) {
            m = ans;
            printf("m: %d, labels = [%d", m, labels[0]);
            for (int i = 1; i < size; i++) {
                printf(",%d", labels[i]);
            }
            printf("]\n");
        }
    }
    for (int j = i; j < size; j++) {
        swap(labels[i], labels[j]);
        perm(labels, j + 1);
        swap(labels[i], labels[j]);
    }
}

int main() {
    /*     Solution sol;
        long long ans = sol.maxScore(n, edges);
        printf("ans = %lld\n", ans); */
    for (int i = 0; i < size; i++) {
        labels[i] = i + 1;
    }
    perm(labels, 0);
    printf("max: %d\n", m);
    return 0;
}