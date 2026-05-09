#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

const int U = 7;
const int CAP = U * U * U;
bool vis[2][CAP];
class Solution {
public:
    int minGenerations(vector<vector<int>>& points, vector<int>& target) {
        int n = points.size();
        for(int i=0;i<CAP;i++){
            vis[0][i]=0;
        }
        for (auto& p : points) {
            int x = p[0];
            int y = p[1];
            int z = p[2];
            vis[0][encode(x, y, z)] = 1;
        }
        int t = encode(target[0], target[1], target[2]);
        int k = 0;
        int p=0;int q=1;
        while (!vis[p][t]) {
            for(int i=0;i<CAP;i++){
                vis[q][i]=vis[p][i];
            }
            bool ok = false;
            for (int i = 0; i < CAP; i++) {
                if(!vis[p][i]){
                    continue;
                }
                for (int j = i + 1; j < CAP; j++) {
                    if(!vis[p][j]){
                        continue;
                    }
                    int x1;
                    int y1;
                    int z1;
                    int x2;
                    int y2;
                    int z2;
                    decode(i,x1,y1,z1);
                    decode(j,x2,y2,z2);
                    int x=(x1+x2)/2;
                    int y=(y1+y2)/2;
                    int z=(z1+z2)/2;
                    int a=encode(x,y,z);
                    if(!vis[q][a]){
                        vis[q][a]=1;
                        ok=true;
                    }
                }
            }
            if(!ok){
                k=-1;
                break;
            }
            k++;
            swap(p,q);
        }
        return k;
    }
    int encode(int x, int y, int z) { return x + y * U + z * U * U; }
    void decode(int a, int& x, int& y, int& z) {
        x = a % U;
        a /= U;
        y = a % U;
        a /= U;
        z = a;
    }
};

int main() {
    string problemName = "3923";
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
        auto points = jread_vector2d(line_in);
        getline(file_in, line_in);
        auto target = jread_vector(line_in);
        auto res = sol.minGenerations(points, target);
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