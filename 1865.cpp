#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class FindSumPairs {
   public:
    unordered_map<int, int> fre1;
    unordered_map<int, int> fre2;
    vector<int> arr2;
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        for (auto e : nums1) {
            fre1[e]++;
        }
        int n = nums2.size();
        arr2 = vector<int>(n);
        for (int i = 0; i < n; i++) {
            int e = nums2[i];
            fre2[e]++;
            arr2[i] = e;
        }
    }

    void add(int index, int val) {
        int tmp = arr2[index];
        arr2[index] += val;
        fre2[tmp]--;
        if (fre2[tmp] == 0) {
            fre2.erase(tmp);
        }
        fre2[arr2[index]]++;
    }

    int count(int tot) {
        int res = 0;
        for (auto& e : fre1) {
            int target = tot - e.first;
            if (fre2.count(target)) {
                res += e.second * fre2[target];
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1865";
    auto begin = jtimer();
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    while (getline(file_in, line_in)) {
        auto cmd = jread_vector_string(line_in);
        getline(file_in, line_in);
        auto data = jread_vector2d(line_in);
        FindSumPairs sol = FindSumPairs(data[0], data[1]);
        vector<int> res;
        res.push_back(-1);
        int j = 2;
        for (int i = 1; i < cmd.size(); i++) {
            if (cmd[i] == "count") {
                int a = sol.count(data[j][0]);
                res.push_back(a);
            } else if (cmd[i] == "add") {
                sol.add(data[j][0], data[j][1]);
                res.push_back(-1);
            }
            j++;
        }
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