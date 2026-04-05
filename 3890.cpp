#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int N = 1e9;
bool isInit = false;
unordered_map<int, int> mp;
vector<int> arr;
void init() {
    for (int i = 1; i < 1000; i++) {
        for (int j = i; j < 1000; j++) {
            int a = i * i * i + j * j * j;
            if (a <= N) {
                mp[a]++;
            }
        }
    }
    for (auto& e : mp) {
        if (e.second >= 2) {
            arr.push_back(e.first);
        }
    }
    sort(begin(arr), end(arr));
}
class Solution {
   public:
    vector<int> findGoodIntegers(int n) {
        if (!isInit) {
            init();
            isInit = true;
        }
        int l = 0;
        int r = arr.size() - 1;
        int u = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (arr[mid] > n) {
                r = mid - 1;
            } else {
                u = mid;
                l = mid + 1;
            }
        }
        vector<int> res(u + 1);
        for (int i = 0; i <= u; i++) {
            res[i] = arr[i];
        }
        return res;
    }
};

int main() {
    string problemName = "3890";
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
        auto n = jread_int(line_in);
        auto res = sol.findGoodIntegers(n);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
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