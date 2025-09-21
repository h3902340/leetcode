#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
const int LIST = 5;

class MovieRentingSystem {
   public:
    unordered_map<int, set<pair<int, int>>> available;
    unordered_map<ll, int> shopMovieToPrice;
    set<tuple<int, int, int>> rented;
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (auto& e : entries) {
            int shop = e[0];
            int movie = e[1];
            int price = e[2];
            available[movie].insert({price, shop});
            shopMovieToPrice[((ll)shop << 32) + movie] = price;
        }
    }

    vector<int> search(int movie) {
        vector<int> res;
        int i = 0;
        for (auto& e : available[movie]) {
            res.push_back(e.second);
            i++;
            if (i == LIST) {
                break;
            }
        }
        return res;
    }

    void rent(int shop, int movie) {
        ll key = ((ll)shop << 32) + movie;
        int price = shopMovieToPrice[key];
        available[movie].erase({price, shop});
        rented.insert({price, shop, movie});
    }

    void drop(int shop, int movie) {
        ll key = ((ll)shop << 32) + movie;
        int price = shopMovieToPrice[key];
        available[movie].insert({price, shop});
        rented.erase({price, shop, movie});
    }

    vector<vector<int>> report() {
        vector<vector<int>> res;
        int i = 0;
        for (auto& e : rented) {
            res.push_back({get<1>(e), get<2>(e)});
            i++;
            if (i == LIST) {
                break;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "1912";
    auto begin = jtimer();
    vector<string> cmd = {"MovieRentingSystem",
                          "search",
                          "rent",
                          "rent",
                          "report",
                          "drop",
                          "search"};
    int n = 3;
    vector<vector<int>> entries = {{0, 1, 5}, {0, 2, 6}, {0, 3, 7},
                                   {1, 1, 4}, {1, 2, 7}, {2, 1, 5}};
    vector<vector<int>> inputs = {{}, {1}, {0, 1}, {1, 2}, {}, {1, 2}, {2}};
    vector<vector<int>> ans = {{}, {1, 0, 2}, {}, {}, {}, {}, {0, 1}};
    vector<vector<vector<int>>> ans2d = {{}, {}, {}, {}, {{0, 1}, {1, 2}},
                                         {}, {}};
    MovieRentingSystem sol(n, entries);
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 1;
    int passCount = 0;
    for (int i = 0; i < cmd.size(); i++) {
        string& e = cmd[i];
        if (e == "MovieRentingSystem") {
            continue;
        }
        if (e == "search") {
            if (sol.search(inputs[i][0]) != ans[i]) {
                allPass = false;
                printf("search is wrong! i:%d\n", i);
                break;
            }
            continue;
        }
        if (e == "rent") {
            sol.rent(inputs[i][0], inputs[i][1]);
            continue;
        }
        if (e == "drop") {
            sol.drop(inputs[i][0], inputs[i][1]);
            continue;
        }
        if (e == "report") {
            if (sol.report() != ans2d[i]) {
                allPass = false;
                printf("report is wrong! i:%d\n", i);
                jprint(sol.report(), "res");
                jprint(ans2d[i], "ans");
                break;
            }
        }
    }
    if (allPass) {
        passCount++;
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    } else {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}