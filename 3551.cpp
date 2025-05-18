#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Node {
    int i;
    int v;
};
class Solution {
   public:
    int minSwaps(vector<int>& nums) {
        vector<vector<Node>> fre(82, vector<Node>());
        vector<int> cnt(82);
        for (int i = 0; i < nums.size(); i++) {
            int ori = nums[i];
            int s = 0;
            while (ori > 0) {
                s += ori % 10;
                ori /= 10;
            }
            fre[s].push_back({i, nums[i]});
            cnt[s]++;
        }
        int ans = 0;
        int k = 0;
        for (int i = 1; i < 82; i++) {
            std::sort(
                fre[i].begin(), fre[i].end(),
                [](const auto& lhs, const auto& rhs) { return lhs.v < rhs.v; });
        }
        for (int i = 1; i < 82; i++) {
            for (int j = 0; j < fre[i].size(); j++) {
                if (nums[k] != fre[i][j].v) {
                    int ori = nums[k];
                    int s = 0;
                    while (ori > 0) {
                        s += ori % 10;
                        ori /= 10;
                    }
                    int l = 0;
                    int r = fre[s].size() - 1;
                    bool notFound = true;
                    while (l <= r) {
                        int mid = (l + r) >> 1;
                        if (fre[s][mid].v > nums[k]) {
                            r = mid - 1;
                        } else if (fre[s][mid].v < nums[k]) {
                            l = mid + 1;
                        } else {
                            fre[s][mid].i = fre[i][j].i;
                            notFound = false;
                            break;
                        }
                    }
                    swap(nums[k], nums[fre[i][j].i]);
                    ans++;
                }
                k++;
            }
        }
        return ans;
    }
};

int main() {
    string problemName = "3551";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    while (getline(file_in, line_in)) {
        auto nums = jread_vector(line_in);
        auto res = sol.minSwaps(nums);
        getline(file_out, line_out);
        auto ans = jread_int(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_int(res, "res");
        jprint_int(ans, "ans");
        printf("\n");
    }
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}