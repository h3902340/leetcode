#include <vector>
using namespace std;

struct Component
{
    vector<int> nodes;
    int edgeCount;
};

class Solution
{
public:
    int countCompleteComponents(int n, vector<vector<int>> &edges)
    {
        vector<int> componentIndex(n, -1);
        vector<Component> components;
        int e = edges.size();
        for (int i = 0; i < e; i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int uIndex = componentIndex[u];
            int vIndex = componentIndex[v];
            if (uIndex == -1)
            {
                if (vIndex == -1)
                {
                    componentIndex[u] = components.size();
                    componentIndex[v] = components.size();
                    components.push_back({{u, v}, 1});
                }
                else
                {
                    components[vIndex].nodes.push_back(u);
                    components[vIndex].edgeCount++;
                    componentIndex[u] = vIndex;
                }
            }
            else
            {
                if (vIndex == -1)
                {
                    components[uIndex].nodes.push_back(v);
                    components[uIndex].edgeCount++;
                    componentIndex[v] = uIndex;
                }
                else
                {
                    if (uIndex == vIndex)
                    {
                        components[uIndex].edgeCount++;
                    }
                    else
                    {
                        for (int j = 0; j < components[vIndex].nodes.size(); j++)
                        {
                            componentIndex[components[vIndex].nodes[j]] = uIndex;
                        }
                        components[uIndex].nodes.insert(components[uIndex].nodes.begin(), components[vIndex].nodes.begin(), components[vIndex].nodes.end());
                        components[uIndex].edgeCount += (components[vIndex].edgeCount + 1);
                        components[vIndex].edgeCount = 0;
                    }
                }
            }
        }
        int ans = 0;
        int isolatedVertexCount = n;
        for (int i = 0; i < components.size(); i++)
        {
            int edgeCount = components[i].edgeCount;
            if (edgeCount == 0)
                continue;
            int nodeCount = components[i].nodes.size();
            ans += (edgeCount == nodeCount * (nodeCount - 1) >> 1);
            isolatedVertexCount -= nodeCount;
        }
        ans += isolatedVertexCount;
        return ans;
    }
};

int n = 6;
vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {3, 4}};

int main()
{
    Solution sol;
    int ans = sol.countCompleteComponents(n, edges);
    printf("ans = %d\n", ans);
    return 0;
}