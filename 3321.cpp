#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

#define ll long long
struct Data {
    int val;
    int cnt;
};
static bool isSmaller(int val, int cnt, Data b) {
    if (cnt == b.cnt) {
        return val < b.val;
    }
    return cnt < b.cnt;
};
static bool isBigger(int val, int cnt, Data b) {
    if (cnt == b.cnt) {
        return val > b.val;
    }
    return cnt > b.cnt;
};
auto mincmp = [](Data& a, Data& b) {
    if (a.cnt == b.cnt) {
        return a.val > b.val;
    }
    return a.cnt > b.cnt;
};
auto maxcmp = [](Data& a, Data& b) {
    if (a.cnt == b.cnt) {
        return a.val < b.val;
    }
    return a.cnt < b.cnt;
};
class Solution {
   public:
    vector<long long> findXSum(vector<int>& nums, const int k, const int x) {
        int n = nums.size();
        priority_queue<Data, vector<Data>, decltype(mincmp)> minQ(mincmp);
        priority_queue<Data, vector<Data>, decltype(maxcmp)> maxQ(maxcmp);
        unordered_map<int, int> freq;
        for (int i = 0; i < k; i++) {
            freq[nums[i]]++;
        }
        vector<Data> arr(freq.size());
        int sz = 0;
        for (auto& f : freq) {
            arr[sz++] = {f.first, f.second};
        }
        sort(begin(arr), end(arr), mincmp);
        int len = min(x, sz);
        vector<ll> res(n - k + 1);
        int idx = 0;
        unordered_set<int> inQ;
        for (int i = 0; i < len; i++) {
            minQ.push(arr[i]);
            inQ.insert(arr[i].val);
            res[idx] += (ll)arr[i].val * arr[i].cnt;
        }
        for (int i = len; i < sz; i++) {
            maxQ.push(arr[i]);
        }
        int i = 0;
        for (int j = k; j < n; j++) {
            int l = nums[i];
            int r = nums[j];
            ll sum = res[idx];
            while (!maxQ.empty()) {
                Data t = maxQ.top();
                if (!inQ.count(t.val) && freq[t.val] > 0 &&
                    freq[t.val] == t.cnt) {
                    break;
                }
                maxQ.pop();
            }
            if (maxQ.empty()) {
                freq[l]--;
                sum -= l;
                if (freq[l] == 0) {
                    inQ.erase(l);
                } else {
                    minQ.push({l, freq[l]});
                }
            } else {
                if (isBigger(l, freq[l], maxQ.top())) {
                    freq[l]--;
                    if (freq[l] == 0) {
                        Data t = maxQ.top();
                        maxQ.pop();
                        minQ.push(t);
                        inQ.erase(l);
                        inQ.insert(t.val);
                        sum = sum - l + t.val * t.cnt;
                    } else if (isBigger(l, freq[l], maxQ.top())) {
                        sum -= l;
                        minQ.push({l, freq[l]});
                    } else {
                        Data t = maxQ.top();
                        maxQ.pop();
                        if (freq[l] > 0) {
                            maxQ.push({l, freq[l]});
                        }
                        minQ.push(t);
                        inQ.erase(l);
                        inQ.insert(t.val);
                        sum = sum - (ll)l * (freq[l] + 1) + (ll)t.val * t.cnt;
                    }
                } else {
                    freq[l]--;
                    if (freq[l] > 0) {
                        maxQ.push({l, freq[l]});
                    }
                }
            }
            while (!minQ.empty()) {
                Data t = minQ.top();
                if (inQ.count(t.val) && freq[t.val] > 0 &&
                    freq[t.val] == t.cnt) {
                    break;
                }
                minQ.pop();
            }
            if (inQ.size() < x) {
                if (freq[r] == 0) {
                    inQ.insert(r);
                }
                freq[r]++;
                sum += r;
                minQ.push({r, freq[r]});
            } else {
                if (isSmaller(r, freq[r], minQ.top())) {
                    freq[r]++;
                    if (isSmaller(r, freq[r], minQ.top())) {
                        maxQ.push({r, freq[r]});
                    } else {
                        Data t = minQ.top();
                        minQ.pop();
                        minQ.push({r, freq[r]});
                        maxQ.push(t);
                        inQ.erase(t.val);
                        inQ.insert(r);
                        sum = sum - (ll)t.val * t.cnt + (ll)r * freq[r];
                    }
                } else {
                    freq[r]++;
                    minQ.push({r, freq[r]});
                    sum += r;
                }
            }
            res[++idx] = sum;
            i++;
        }
        return res;
    }
};

int main() {
    string problemName = "3321";
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
        auto nums = jread_vector(line_in);
        getline(file_in, line_in);
        auto k = jread_int(line_in);
        getline(file_in, line_in);
        auto x = jread_int(line_in);
        auto res = sol.findXSum(nums, k, x);
        getline(file_out, line_out);
        auto ans = jread_vector_longlong(line_out);
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