#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Data {
    int userId;
    int bid;
};
class Cmp {
   public:
    bool operator()(Data& a, Data& b) {
        if (a.bid == b.bid) {
            return a.userId < b.userId;
        }
        return a.bid < b.bid;
    }
};
class AuctionSystem {
   public:
    unordered_map<int, unordered_map<int, int>> bid;
    unordered_map<int, priority_queue<Data, vector<Data>, Cmp>> pq;
    AuctionSystem() {}

    void addBid(int userId, int itemId, int bidAmount) {
        bid[userId][itemId] = bidAmount;
        pq[itemId].push({userId, bidAmount});
    }

    void updateBid(int userId, int itemId, int newAmount) {
        addBid(userId, itemId, newAmount);
    }

    void removeBid(int userId, int itemId) { bid[userId][itemId] = 0; }

    int getHighestBidder(int itemId) {
        while (!pq[itemId].empty()) {
            Data t = pq[itemId].top();
            if (bid[t.userId][itemId] == t.bid) {
                return t.userId;
            }
            pq[itemId].pop();
        }
        return -1;
    }
};

int main() {
    string problemName = "3815";
    auto begin = jtimer();
    AuctionSystem sol;
    vector<string> input = {
        "AuctionSystem",    "addBid",           "addBid",
        "getHighestBidder", "updateBid",        "getHighestBidder",
        "removeBid",        "getHighestBidder", "getHighestBidder"};
    vector<vector<int>> params = {{},  {1, 7, 5}, {2, 7, 6}, {7}, {1, 7, 8},
                                  {7}, {2, 7},    {7},       {3}};
    vector<int> ans = {0, 0, 0, 2, 0, 1, 0, 1, -1};
    vector<int> res = {0, 0, 0, 2, 0, 1, 0, 1, -1};
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == "addBid") {
            sol.addBid(params[i][0], params[i][1], params[i][2]);
        } else if (input[i] == "getHighestBidder") {
            res[i] = sol.getHighestBidder(params[i][0]);
        } else if (input[i] == "updateBid") {
            sol.updateBid(params[i][0], params[i][1], params[i][2]);
        } else if (input[i] == "removeBid") {
            sol.removeBid(params[i][0], params[i][1]);
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