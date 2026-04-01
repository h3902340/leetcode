#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int i;
    int p;
    int h;
    int d;
    bool operator<(const Data& a) const { return p < a.p; }
    Data& operator=(const Data& a) {
        i = a.i;
        p = a.p;
        h = a.h;
        d = a.d;
        return *this;
    }
};
const int N = 1e5;
Data arr[N];
Data temp[N];
class Solution {
   public:
    vector<int> survivedRobotsHealths(vector<int>& positions,
                                      vector<int>& healths, string directions) {
        int n = positions.size();
        for (int i = 0; i < n; i++) {
            arr[i] = {i, positions[i], healths[i], directions[i]};
        }
        sort(begin(arr), begin(arr) + n);
        int j = -1;
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i].d == 'L') {
                while (j >= 0 && arr[j].h < arr[i].h) {
                    j--;
                    arr[i].h--;
                }
                if (j >= 0) {
                    if (arr[j].h == arr[i].h) {
                        j--;
                    } else {
                        arr[j].h--;
                    }
                } else {
                    temp[k++] = arr[i];
                }
                continue;
            }
            arr[++j] = arr[i];
        }
        for (int i = j; i >= 0; i--) {
            temp[k++] = arr[i];
        }
        auto cmp = [](Data& a, Data& b) { return a.i < b.i; };
        sort(begin(temp), begin(temp) + k, cmp);
        vector<int> res(k);
        for (int i = 0; i < k; i++) {
            res[i] = temp[i].h;
        }
        return res;
    }
};

int main() {
    string problemName = "2751";
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
        auto positions = jread_vector(line_in);
        getline(file_in, line_in);
        auto healths = jread_vector(line_in);
        getline(file_in, line_in);
        auto directions = jread_string(line_in);
        auto res = sol.survivedRobotsHealths(positions, healths, directions);
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