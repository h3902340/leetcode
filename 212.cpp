#include <vector>

#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

struct Trie {
    int idx[26];
    int wordIdx;
};
const int WORDLEN = 10;
const int WORDCOUNT = 3e4;
Trie trie[WORDLEN * WORDCOUNT];
struct Node {
    int index;
    int i;
    int j;
    int c;
};
const int M = 12;
const int N = 12;
Node s[M * N];
const int dir[4][2]{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
   public:
    vector<string> findWords(vector<vector<char>>& board,
                             vector<string>& words) {
        int m = board.size();
        int n = board[0].size();
        int boardSize = m * n;
        memset(trie[0].idx, -1, sizeof(trie[0].idx));
        trie[0].wordIdx = -1;
        int j = 0;
        for (int k = 0; k < words.size(); k++) {
            string& w = words[k];
            int i = 0;
            for (auto& c : w) {
                if (trie[i].idx[c - 'a'] == -1) {
                    trie[i].idx[c - 'a'] = ++j;
                    memset(trie[j].idx, -1, sizeof(trie[j].idx));
                    trie[j].wordIdx = -1;
                }
                i = trie[i].idx[c - 'a'];
            }
            trie[i].wordIdx = k;
        }
        vector<string> res;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int c = board[i][j] - 'a';
                if (trie[0].idx[c] == -1) continue;
                int r = 0;
                s[r].index = trie[0].idx[c];
                s[r].i = i;
                s[r].j = j;
                while (r >= 0) {
                    Node& t = s[r];
                    int wordIdx = trie[t.index].wordIdx;
                    if (wordIdx != -1) {
                        res.push_back(words[wordIdx]);
                        trie[t.index].wordIdx = -1;
                    }
                    if (board[t.i][t.j] == 'X') {
                        board[t.i][t.j] = t.c;
                        r--;
                        continue;
                    }
                    t.c = board[t.i][t.j];
                    board[t.i][t.j] = 'X';
                    for (int k = 0; k < 4; k++) {
                        int inew = t.i + dir[k][0];
                        int jnew = t.j + dir[k][1];
                        if (inew < 0 || inew >= m || jnew < 0 || jnew >= n)
                            continue;
                        if (board[inew][jnew] == 'X') continue;
                        int d = board[inew][jnew] - 'a';
                        int idx = trie[t.index].idx[d];
                        if (idx == -1) continue;
                        r++;
                        s[r].index = idx;
                        s[r].i = inew;
                        s[r].j = jnew;
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    string problemName = "212";
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
        auto board = jread_vector2d_char(line_in);
        getline(file_in, line_in);
        auto words = jread_vector_string(line_in);
        auto res = sol.findWords(board, words);
        getline(file_out, line_out);
        auto ans = jread_vector_string(line_out);
        printf("Case %d", ++caseCount);
        if (anyOrderEqual(res, ans)) {
            passCount++;
            printf(" %s(PASS)", KGRN);
        } else {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint_vector_string(res, "res");
        jprint_vector_string(ans, "ans");
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