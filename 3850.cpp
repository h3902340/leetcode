#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int LO = -12;
const int HI = 38;
const int B = HI - LO + 1;
const int U = 6;
const int p[3]{2, 3, 5};
const int EXP[U + 1]{0,
                     -LO - LO* B - LO * B * B,
                     -LO + 1 - LO* B - LO * B * B,
                     -LO + (-LO + 1) * B - LO * B * B,
                     -LO + 2 - LO* B - LO * B * B,
                     -LO - LO* B + (-LO + 1) * B* B,
                     -LO + 1 + (-LO + 1) * B - LO * B * B};

class Solution {
   public:
    int countSequences(vector<int>& nums, long long k) {
        int n = nums.size();
        int v = 0;
        for (int i = 2; i >= 0; i--) {
            int e = 0;
            while (k % p[i] == 0) {
                k /= p[i];
                e++;
            }
            v = (v * B) + e - LO;
        }
        if (k > 1) {
            return 0;
        }
        unordered_map<int, int> mp;
        unordered_map<int, int> mp2;
        mp[EXP[1]] = 1;
        for (int i = 0; i < n; i++) {
            mp2.clear();
            for (auto& e : mp) {
                mp2[e.first] += e.second;
                mp2[e.first + EXP[nums[i]] - EXP[1]] += e.second;
                int a = e.first;
                int b = EXP[nums[i]];
                bool ok = true;
                for (int j = 0; j < 3; j++) {
                    int x = a % B;
                    int y = b % B;
                    a /= B;
                    b /= B;
                    if (x - y < LO) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    mp2[e.first - EXP[nums[i]] + EXP[1]] += e.second;
                }
            }
            swap(mp, mp2);
        }
        return mp[v];
    }
};

int main() {
    string problemName = "3850";
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
        getline(file_in, line_in);
        auto k = jread_longlong(line_in);
        auto res = sol.countSequences(nums, k);
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
        jprint(res, "res");
        jprint(ans, "ans");
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