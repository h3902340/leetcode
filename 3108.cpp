#include <vector>
using namespace std;

struct Component
{
    vector<int> vertices;
    int totalWeight;
};

class Solution
{
public:
    vector<int> minimumCost(int n, vector<vector<int>> &edges, vector<vector<int>> &query)
    {
        int E = edges.size();
        vector<int> componentIndex(n, -1);
        vector<Component> components;
        for (int i = 0; i < E; i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            int uIndex = componentIndex[u];
            int vIndex = componentIndex[v];
            if (uIndex == -1)
            {
                if (vIndex == -1)
                {
                    Component component = {{u, v}, w};
                    componentIndex[u] = components.size();
                    componentIndex[v] = components.size();
                    components.push_back(component);
                }
                else
                {
                    components[vIndex].vertices.push_back(u);
                    componentIndex[u] = vIndex;
                    components[vIndex].totalWeight &= w;
                }
            }
            else
            {
                if (vIndex == -1)
                {
                    components[uIndex].vertices.push_back(v);
                    componentIndex[v] = uIndex;
                    components[uIndex].totalWeight &= w;
                }
                else
                {
                    if (uIndex == vIndex)
                    {
                        components[uIndex].totalWeight &= w;
                    }
                    else
                    {
                        for (int j = 0; j < components[vIndex].vertices.size(); j++)
                        {
                            components[uIndex].vertices.push_back(components[vIndex].vertices[j]);
                            componentIndex[components[vIndex].vertices[j]] = uIndex;
                        }
                        components[uIndex].totalWeight &= w;
                        components[uIndex].totalWeight &= components[vIndex].totalWeight;
                    }
                }
            }
        }
        int Q = query.size();
        vector<int> ans(Q);
        for (int i = 0; i < Q; i++)
        {
            int uIndex = componentIndex[query[i][0]];
            int vIndex = componentIndex[query[i][1]];
            if (uIndex == -1 || vIndex == -1)
            {
                ans[i] = -1;
                continue;
            }
            if (uIndex == vIndex)
            {
                ans[i] = components[uIndex].totalWeight;
                continue;
            }
            ans[i] = -1;
        }
        return ans;
    }
};

int n = 5;
vector<vector<int>> edges = {{0, 1, 7}, {1, 3, 7}, {1, 2, 1}};
vector<vector<int>> query = {{0, 3}, {3, 4}};

int main()
{
    Solution sol;
    vector<int> ans = sol.minimumCost(n, edges, query);
    printf("ans = [");
    for (int i = 0; i < ans.size() - 1; i++)
    {
        printf("%d, ", ans[i]);
    }
    printf("%d]\n", ans[ans.size() - 1]); // [1, -1]
    return 0;
}