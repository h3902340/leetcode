#include <vector>
using namespace std;

// TODO: use union-find instead
class Solution {
   public:
    int numberOfComponents(vector<vector<int>> &properties, int k) {
        int n = properties.size();
        int m = properties[0].size();
        vector<int> componentIndex(n);
        vector<vector<int>> components(n);
        for (int i = 0; i < n; i++) {
            componentIndex[i] = i;
            components[i] = {i};
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                int uCounter[101]{0};
                for (int k = 0; k < m; k++) {
                    uCounter[properties[i][k]] = 1;
                }
                int vCounter[101]{0};
                for (int k = 0; k < m; k++) {
                    vCounter[properties[j][k]] = 1;
                }
                for (int k = 0; k < 101; k++) {
                    uCounter[k] += vCounter[k];
                }
                int common = 0;
                for (int k = 0; k < 101; k++) {
                    common += uCounter[k] > 1;
                }
                if (common < k) continue;
                int uIndex = componentIndex[i];
                int vIndex = componentIndex[j];
                if (uIndex == vIndex) continue;
                vector<int> *uComp = &components[uIndex];
                vector<int> *vComp = &components[vIndex];
                uComp->insert(uComp->end(), vComp->begin(), vComp->end());
                for (int k = 0; k < vComp->size(); k++) {
                    componentIndex[vComp->at(k)] = uIndex;
                }
                vComp->clear();
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += components[i].size() > 0;
        }
        return ans;
    }
};

vector<vector<int>> properties = {{1, 2}, {1, 1}, {3, 4},
                                  {4, 5}, {5, 6}, {7, 7}};
int k = 1;

int main() {
    Solution sol;
    int ans = sol.numberOfComponents(properties, k);
    printf("ans = %d\n", ans);  // 3
    return 0;
}