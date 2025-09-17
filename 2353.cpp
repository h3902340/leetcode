#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Food {
    string name;
    int rate;
};
struct Comp {
    bool operator()(const Food& a, const Food& b) const {
        if (a.rate == b.rate) {
            int az = a.name.size();
            int bz = b.name.size();
            int n = min(az, bz);
            for (int i = 0; i < n; i++) {
                if (a.name[i] == b.name[i]) {
                    continue;
                }
                return a.name[i] > b.name[i];
            }
            return az > bz;
        }
        return a.rate < b.rate;
    }
};
class FoodRatings {
   public:
    unordered_map<string, priority_queue<Food, vector<Food>, Comp>>
        cuisineToFood;
    unordered_map<string, string> nameToCuisine;
    unordered_map<string, int> nameToRating;
    FoodRatings(vector<string>& foods, vector<string>& cuisines,
                vector<int>& ratings) {
        int n = foods.size();
        for (int i = 0; i < n; i++) {
            cuisineToFood[cuisines[i]].push({foods[i], ratings[i]});
            nameToCuisine[foods[i]] = cuisines[i];
            nameToRating[foods[i]] = ratings[i];
        }
    }

    void changeRating(const string& food, int newRating) {
        string type = nameToCuisine[food];
        int score = nameToRating[food];
        Food f = {food, score};
        Food newf = {food, newRating};
        cuisineToFood[type].push(newf);
        nameToRating[food] = newRating;
    }

    string highestRated(const string& cuisine) {
        auto& pq = cuisineToFood[cuisine];
        while (!pq.empty()) {
            Food t = pq.top();
            if (nameToRating[t.name] == t.rate) {
                return t.name;
            }
            pq.pop();
        }
        return "";
    }
};

int main() {
    printf("1\n");
    string problemName = "2353";
    auto begin = jtimer();
    vector<string> cmd = {"FoodRatings",  "highestRated", "highestRated",
                          "changeRating", "highestRated", "changeRating",
                          "highestRated"};
    vector<string> keys = {"",         "korean", "japanese", "sushi",
                           "japanese", "ramen",  "japanese"};
    vector<int> values = {0, 0, 0, 16, 0, 16, 0};
    vector<string> foods = {"kimchi",   "miso",  "sushi",
                            "moussaka", "ramen", "bulgogi"};
    vector<string> cuisunes = {"korean", "japanese", "japanese",
                               "greek",  "japanese", "korean"};
    vector<int> ratings = {9, 12, 8, 15, 14, 7};
    vector<string> ans = {"", "kimchi", "ramen", "", "sushi", "", "ramen"};
    FoodRatings sol(foods, cuisunes, ratings);
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    for (int i = 0; i < cmd.size(); i++) {
        string& e = cmd[i];
        if (e == "FoodRatings") {
            // sol = FoodRatings(foods, cuisunes, ratings);
        } else if (e == "highestRated") {
            if (sol.highestRated(keys[i]) != ans[i]) {
                printf("res:%s,ans:%s\n", sol.highestRated(keys[i]).c_str(),
                       ans[i].c_str());
                allPass = false;
                break;
            }
        } else if (e == "changeRating") {
            sol.changeRating(keys[i], values[i]);
        }
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