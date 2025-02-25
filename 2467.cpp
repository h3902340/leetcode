#include <chrono>
#include <cstdio>
#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution
{
public:
    int mostProfitablePath(vector<vector<int>> &edges, int bob, vector<int> &amount)
    {
        // making adjacency list
        int n = amount.size();
        vector<vector<int>> adjacency(n);
        for (int i = 0; i < edges.size(); i++)
        {
            adjacency[edges[i][0]].push_back(edges[i][1]);
            adjacency[edges[i][1]].push_back(edges[i][0]);
        }
        // finding Bob's path
        stack<int> path;
        stack<int> indexTemp;
        int index = 0;
        while (true)
        {
            if (bob == 0)
                break;
            if (index < adjacency[bob].size())
            {
                if (!path.empty() && adjacency[bob][index] == path.top())
                {
                    index++;
                    continue;
                }
                path.push(bob);
                indexTemp.push(index);
                bob = adjacency[bob][index];
                index = 0;
                continue;
            }
            index = indexTemp.top() + 1;
            bob = path.top();
            indexTemp.pop();
            path.pop();
        }
        // updating amount by Bob's path
        int bobPathSize = path.size();
        for (int i = 0; i < (bobPathSize - 1) >> 1; i++)
        {
            path.pop();
        }
        if (bobPathSize % 2 == 0)
        {
            amount[path.top()] *= .5;
            path.pop();
        }
        for (int i = 0; i < (bobPathSize + 1) >> 1; i++)
        {
            amount[path.top()] = 0;
            path.pop();
        }
        // finding maximum profit
        int alice = 0;
        int currentProfit = amount[alice];
        int maxProfit = INT_MIN;
        indexTemp = stack<int>();
        index = 0;
        while (true)
        {
            if (adjacency[alice].size() == 1 && alice != 0)
            {
                if (currentProfit > maxProfit)
                {
                    maxProfit = currentProfit;
                }
            }
            if (index < adjacency[alice].size())
            {
                if (!path.empty() && adjacency[alice][index] == path.top())
                {
                    index++;
                    continue;
                }
                path.push(alice);
                indexTemp.push(index);
                alice = adjacency[alice][index];
                index = 0;
                currentProfit += amount[alice];
                continue;
            }
            if (path.size() == 0)
                break;
            currentProfit -= amount[alice];
            index = indexTemp.top() + 1;
            alice = path.top();
            indexTemp.pop();
            path.pop();
        }
        return maxProfit;
    }
};

vector<vector<int>> edges = {{0,1},{1,2},{2,3}};
int bob = 3;
vector<int> amount = {-5644,-6018,1188,-8502};

int main()
{
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    Solution sol;
    int ans = sol.mostProfitablePath(edges, bob, amount);
    printf("max profit: %d\n", ans);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time difference = "
         << chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << "[ms]\n";
    return 0;
}