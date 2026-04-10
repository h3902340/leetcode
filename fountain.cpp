#include <cstdint>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Data {
    int h;
    int i;
};
vector<bool> solve(vector<int>& height, vector<int>& fountain) {
    int n = height.size();
    int m = fountain.size();
    vector<bool> res(n, false);
    // left to right
    stack<Data> st;
    st.push({INT32_MAX, -1});  // sentinel
    int j = 0;
    int k = 0;
    for (int i = 0; i < n; i++) {
        while (st.top().h <= height[i]) {
            st.pop();
        }
        if (i == fountain[j]) {
            for (k = max(k, st.top().i + 1); k < i; k++) {
                if (height[k] == height[i]) {
                    continue;
                }
                res[k] = true;
            }
            j++;
            if (j == m) {
                break;
            }
        }
        st.push({height[i], i});
    }
    // right to left
    stack<Data> st2;
    st2.push({INT32_MAX, n});  // sentinel
    j = m - 1;
    k = n - 1;
    for (int i = n - 1; i >= 0; i--) {
        while (st2.top().h <= height[i]) {
            st2.pop();
        }
        if (i == fountain[j]) {
            for (k = min(k, st2.top().i - 1); k > i; k--) {
                if (height[k] == height[i]) {
                    continue;
                }
                res[k] = true;
            }
            j--;
            if (j == -1) {
                break;
            }
        }
        st2.push({height[i], i});
    }
    return res;
}

struct Data2 {
    int pre;
    int nxt;
    int h;
};
vector<bool> solve2(vector<int>& height, vector<int>& fountain) {
    int n = height.size();
    int m = fountain.size();
    vector<Data2> list(n);
    for (int i = 0; i < n; i++) {
        list[i].pre = i - 1;
        list[i].nxt = i + 1;
        list[i].h = height[i];
    }
    vector<bool> isFountain(n, false);
    for (int i = 0; i < m; i++) {
        isFountain[fountain[i]] = true;
    }
    vector<bool> res(n, false);
    for (int i = 0; i < n; i++) {
        if (!isFountain[i]) {
            continue;
        }
        if (res[i]) {
            continue;
        }
        while (list[i].pre != -1 && list[list[i].pre].h <= list[i].h) {
            if (list[list[i].pre].h < list[i].h) {
                res[list[i].pre] = true;
            }
            if (list[list[i].pre].pre != -1) {
                list[list[list[i].pre].pre].nxt = i;
            }
            list[i].pre = list[list[i].pre].pre;
        }
        while (list[i].nxt != n && list[list[i].nxt].h <= list[i].h) {
            if (list[list[i].nxt].h < list[i].h) {
                res[list[i].nxt] = true;
            }
            if (list[list[i].nxt].nxt != n) {
                list[list[list[i].nxt].nxt].pre = i;
            }
            list[i].nxt = list[list[i].nxt].nxt;
        }
    }
    return res;
}

void test(vector<int>& height, vector<int>& fountain, vector<bool>& ans) {
    vector<bool> res = solve2(height, fountain);
    cout << "res:[";
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << ',';
    }
    cout << "]\n";
    cout << "ans:[";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << ',';
    }
    cout << "]\n";
}

int main() {
    vector<int> height = {1, 2, 3, 2, 1, 2, 1, 2, 1};
    vector<int> fountain = {7};
    vector<bool> ans = {0, 0, 0, 0, 1, 0, 1, 0, 1};
    test(height, fountain, ans);
    vector<int> height2 = {1, 2, 3, 2, 1, 4};
    vector<int> fountain2 = {2, 5};
    vector<bool> ans2 = {1, 1, 1, 1, 1, 0};
    test(height2, fountain2, ans2);
}