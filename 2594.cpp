#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;
struct Mechanic
{
    int sameCount;
    long completeCar;
    long rank;
    long time;
};
class Solution
{
public:
    // I use min heap because binary search is not creative.
    long long repairCars(vector<int> &ranks, int cars)
    {
        int n = ranks.size();
        auto compare = [](Mechanic a, Mechanic b)
        {
            return a.time > b.time;
        };
        priority_queue<Mechanic, vector<Mechanic>, decltype(compare)> pq(compare);
        unordered_map<int, int> sameRankMap;
        for (int i = 0; i < n; i++)
        {
            sameRankMap[ranks[i]]++;
        }
        for (auto entry : sameRankMap)
        {
            Mechanic mec = {entry.second, 1, entry.first, entry.first};
            pq.push(mec);
        }
        long minTime = 0;
        while (cars > 0)
        {
            Mechanic min = pq.top();
            pq.pop();
            cars -= min.sameCount;
            minTime = min.time;
            long completeCar = min.completeCar + 1;
            long time = min.time + min.rank * ((min.completeCar << 1) + 1);
            min = {min.sameCount, completeCar, min.rank, time};
            pq.push(min);
        }
        return minTime;
    }
};

vector<int> ranks = {4, 2, 3, 1};
int cars = 10;

int main()
{
    Solution sol;
    long long ans = sol.repairCars(ranks, cars);
    printf("ans = %lld\n", ans); // 16
    return 0;
}