#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// TODO: time is bad (1222 ms)
class Solution {
   public:
    string findCommonResponse(vector<vector<string>> &responses) {
        unordered_map<string, int> map;
        for (int i = 0; i < responses.size(); i++) {
            unordered_set<string> set;
            for (int j = 0; j < responses[i].size(); j++) {
                if (!set.count(responses[i][j])) {
                    set.insert(responses[i][j]);
                }
            }
            for (auto s : set) {
                map[s]++;
            }
        }
        string ans = "";
        int max = 0;
        for (auto s : map) {
            if (s.second > max) {
                ans = s.first;
                max = s.second;
            } else if (s.second == max) {
                int cap = ans.size();
                if (cap > s.first.size()) {
                    cap = s.first.size();
                }
                bool allSame = true;
                for (int i = 0; i < cap; i++) {
                    if (ans[i] > s.first[i]) {
                        ans = s.first;
                        allSame = false;
                        break;
                    } else if (ans[i] < s.first[i]) {
                        allSame = false;
                        break;
                    }
                }
                if (allSame) {
                    if (ans.size() > s.first.size()) {
                        ans = s.first;
                    }
                }
            }
        }
        return ans;
    }
};