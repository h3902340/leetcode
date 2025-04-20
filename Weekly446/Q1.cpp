#include <vector>
using namespace std;

class Solution
{
public:
    long long calculateScore(vector<string> &instructions, vector<int> &values)
    {
        int n = instructions.size();
        int i = 0;
        long long score = 0;
        bool isEnd = false;
        while (i >= 0 && i < n && !isEnd)
        {
            switch (instructions[i][0])
            {
            case 'j':
                instructions[i] = "z";
                i += values[i];
                break;
            case 'a':
                score += values[i];
                instructions[i] = "z";
                i++;
                break;
            default:
                isEnd = true;
                break;
            }
        }
        return score;
    }
};

vector<string> instructions = {"jump", "add", "add", "jump", "add", "jump"};
vector<int> values = {2, 1, 3, 1, -2, -3};

int main()
{
    Solution sol;
    long long ans = sol.calculateScore(instructions, values);
    printf("score = %lld\n", ans);
    return 0;
}