#include <vector>
using namespace std;

struct Path
{
    int endPoint;
    long time;
    int way;
};
class Solution
{
public:
    int countPaths(int n, vector<vector<int>> &roads)
    {
        if (n == 1)
            return 1;
        int r = roads.size();
        vector<vector<int>> dist(n, vector<int>(n, -1));
        for (int i = 0; i < r; i++)
        {
            dist[roads[i][0]][roads[i][1]] = roads[i][2];
            dist[roads[i][1]][roads[i][0]] = roads[i][2];
        }
        vector<Path> paths(n - 1);
        for (int i = 1; i < n; i++)
        {
            paths[i - 1] = {i, dist[0][i], 1};
        }
        int minIndex = 0;
        int min = (paths[0].time == -1) ? INT_MAX : paths[0].time;
        for (int i = 1; i < n - 1; i++)
        {
            if (paths[i].time != -1 && paths[i].time < min)
            {
                minIndex = i;
                min = paths[i].time;
            }
        }
        Path temp = paths[0];
        paths[0] = paths[minIndex];
        paths[minIndex] = temp;
        minIndex = 0;
        for (int j = 0; j < n - 2; j++)
        {
            long nextMin = LONG_MAX;
            int nextMinIndex = -1;
            for (int i = minIndex + 1; i < n - 1; i++)
            {
                int d = dist[paths[minIndex].endPoint][paths[i].endPoint];
                if (d != -1)
                {
                    long alternative = paths[minIndex].time + d;
                    if (paths[i].time == -1 || alternative < paths[i].time)
                    {
                        paths[i].time = alternative;
                        paths[i].way = paths[minIndex].way;
                    }
                    else if (alternative == paths[i].time)
                    {
                        paths[i].way = (paths[i].way + paths[minIndex].way) % 1000000007;
                    }
                }
                if (paths[i].time != -1 && paths[i].time < nextMin)
                {
                    nextMin = paths[i].time;
                    nextMinIndex = i;
                }
            }
            minIndex++;
            Path temp = paths[minIndex];
            paths[minIndex] = paths[nextMinIndex];
            paths[nextMinIndex] = temp;
            if (paths[minIndex].endPoint == n - 1)
            {
                break;
            }
        }
        return paths[minIndex].way;
    }
};

int n = 7;
vector<vector<int>> roads = {{0, 6, 7}, {0, 1, 2}, {1, 2, 3}, {1, 3, 3}, {6, 3, 3}, {3, 5, 1}, {6, 5, 1}, {2, 5, 1}, {0, 4, 5}, {4, 6, 2}};

int main()
{
    Solution sol;
    int ans = sol.countPaths(n, roads);
    printf("ans = %d\n", ans); // 4
    return 0;
}