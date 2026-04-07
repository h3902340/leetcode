#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Robot {
   public:
    int w;
    int h;
    int round;
    bool touch;
    int x;
    int y;
    int r;
    Robot(int width, int height) {
        w = width;
        h = height;
        round = w * 2 + h * 2 - 4;
        touch = false;
        x = 0;
        y = 0;
        r = 1;
    }

    void step(int num) {
        if (!touch) {
            x += num;
            if (x > w - 1) {
                int left = x - w + 1;
                touch = true;
                x = w - 1;
                step(left);
            }
            return;
        }
        num %= round;
        if (num / round > 0) {
            if (x == 0 && y == 0) {
                r = 2;
            } else if (x == w - 1 && y == 0) {
                r = 1;
            } else if (x == w - 1 && y == h - 1) {
                r = 0;
            } else if (x == 0 && y == h - 1) {
                r = 3;
            }
        }
        if (num == 0) {
            return;
        }
        int left = 0;
        if (r == 0) {
            y += num;
            if (y > h - 1) {
                left = y - h + 1;
                y = h - 1;
                r = (r + 3) % 4;
            }
        } else if (r == 1) {
            x += num;
            if (x > w - 1) {
                left = x - w + 1;
                x = w - 1;
                r = (r + 3) % 4;
            }
        } else if (r == 2) {
            y -= num;
            if (y < 0) {
                left = -y;
                y = 0;
                r = (r + 3) % 4;
            }
        } else {
            x -= num;
            if (x < 0) {
                left = -x;
                x = 0;
                r = (r + 3) % 4;
            }
        }
        if (left > 0) {
            step(left);
        }
    }

    vector<int> getPos() { return {x, y}; }

    string getDir() {
        if (r == 0) {
            return "North";
        } else if (r == 1) {
            return "East";
        } else if (r == 2) {
            return "South";
        } else {
            return "West";
        }
    }
};

int main() {
    string problemName = "2069";
    auto begin = jtimer();
    //[]
    //[[6,3],[2],[2],[],[],[2],[1],[4],[],[]]
    Robot sol(6, 3);
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    vector<string> cmd = {"Robot", "step", "step", "getPos", "getDir",
                          "step",  "step", "step", "getPos", "getDir"};
    vector<vector<int>> param = {{6, 3}, {2}, {2}, {}, {},
                                 {2},    {1}, {4}, {}, {}};
    vector<vector<int>> ans = {{}, {}, {}, {4, 0}, {1},
                               {}, {}, {}, {1, 2}, {3}};
    vector<vector<int>> res;
    for (int i = 0; i < cmd.size(); i++) {
        if (cmd[i] == "step") {
            sol.step(param[i][0]);
            res.push_back({});
        } else if (cmd[i] == "getPos") {
            res.push_back(sol.getPos());
        } else if (cmd[i] == "getDir") {
            string dir = sol.getDir();
            vector<int> a(1);
            if (dir == "North") {
                a[0] = 0;
            } else if (dir == "East") {
                a[0] = 1;
            } else if (dir == "South") {
                a[0] = 2;
            } else if (dir == "West") {
                a[0] = 3;
            }
            res.push_back(a);
        } else {
            res.push_back({});
        }
    }
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
    if (allPass) {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}