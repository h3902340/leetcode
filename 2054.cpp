#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int t;
    int v;
};
const int N = 1e5;
const int BUCKET_SIZE = 256;
const int MASK = 255;
int buckets[BUCKET_SIZE];
Data head[2][N];
Data tail[2][N];
void radixSort(Data arr[2][N], int n) {
    int p = 0;
    int q = 1;
    for (int j = 0; j < 32; j += 8) {
        for (int i = 0; i < n; i++) {
            buckets[(arr[p][i].t >> j) & MASK]++;
        }
        for (int i = 1; i < BUCKET_SIZE; i++) {
            buckets[i] += buckets[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            arr[q][--buckets[(arr[p][i].t >> j) & MASK]] = arr[p][i];
        }
        fill(begin(buckets), end(buckets), 0);
        swap(p, q);
    }
}

class Solution {
   public:
    int maxTwoEvents(vector<vector<int>>& events) {
        int n = events.size();
        for (int i = 0; i < n; i++) {
            tail[0][i] = {events[i][0], events[i][2]};
            head[0][i] = {events[i][1], events[i][2]};
        }
        radixSort(head, n);
        radixSort(tail, n);
        for (int i = 1; i < n; i++) {
            head[0][i].v = max(head[0][i].v, head[0][i - 1].v);
            tail[0][n - 1 - i].v = max(tail[0][n - 1 - i].v, tail[0][n - i].v);
        }
        int res = 0;
        int j = 0;
        for (int i = 0; i < n; i++) {
            int t = head[0][i].t;
            int v = head[0][i].v;
            int l = j;
            int r = n - 1;
            j = n;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (tail[0][mid].t > t) {
                    j = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (j == n) {
                res = max(res, head[0][n - 1].v);
                break;
            }
            v += tail[0][j].v;
            res = max(res, v);
        }
        return res;
    }
};

int main() {
    string problemName = "2054";
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
        auto events = jread_vector2d(line_in);
        auto res = sol.maxTwoEvents(events);
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