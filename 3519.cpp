#include <string>
#include <vector>
using namespace std;
// TODO: optimize to 0 ms
const int MOD = 1000000007;
bool isInit = false;
const int D = 334;
int C[D][D];
const int B = 11;
const int N = 100;
int bases[B][N][D];
static void buildBases()
{
    for (int k = 2; k < B; k++)
    {
        bases[k][0][0] = 1;
        for (int i = 1; i < N; i++)
        {
            for (int j = 0; j < D; j++)
            {
                bases[k][i][j] = bases[k][i - 1][j] * 10;
            }
            for (int j = 0; j < D - 1; j++)
            {
                bases[k][i][j + 1] += bases[k][i][j] / k;
                bases[k][i][j] = bases[k][i][j] % k;
            }
        }
    }
}

static void init()
{
    if (isInit)
        return;
    for (int i = 1; i < D; i++)
    {
        C[i][0] = 1;
        C[i][i] = 1;
        for (int j = 1; j < i; j++)
        {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            if (C[i][j] > MOD)
            {
                C[i][j] -= MOD;
            }
        }
    }
    buildBases();
    isInit = true;
}

class Solution
{
public:
    int countNumbers(string l, string r, int b)
    {
        init();
        int NMAX = r.size();
        int DMAX = int(ceil(100 / log10(b)));
        vector<int> digit_r(DMAX, 0);
        int len_r = 0;
        changeBase(r, b, digit_r, len_r, DMAX);
        int c_r = countNonDecreasing(digit_r, len_r, b);
        vector<int> digit_l(DMAX, 0);
        int len_l = 0;
        changeBase(l, b, digit_l, len_l, DMAX);
        int c_l = countNonDecreasing(digit_l, len_l, b);
        bool is_r_non_decreasing = true;
        for (int i = 1; i < len_r; i++)
        {
            if (digit_r[i] > digit_r[i - 1])
            {
                is_r_non_decreasing = false;
                break;
            }
        }
        int ans = c_r - c_l + is_r_non_decreasing;
        if (ans < 0)
        {
            ans += MOD;
        }
        return ans;
    }

private:
    void changeBase(string s, int b, vector<int> &digit, int &len, int DMAX)
    {
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            int c = n - 1 - i;
            int d = s[i] - '0';
            for (int j = 0; j < DMAX; j++)
            {
                digit[j] += bases[b][c][j] * d;
            }
        }
        for (int j = 0; j < DMAX - 1; j++)
        {
            digit[j + 1] += digit[j] / b;
            digit[j] = digit[j] % b;
        }
        for (int i = DMAX - 1; i >= 0; i--)
        {
            if (digit[i])
            {
                len = i + 1;
                break;
            }
        }
    }
    int countNonDecreasing(vector<int> &digit, int len, int b)
    {
        int c = 0;
        int pre = 0;
        for (int i = len - 1; i >= 0; i--)
        {
            if (pre > digit[i])
                break;
            for (int j = pre; j < digit[i]; j++)
            {
                c += C[b + i - j - 1][i];
                if (c >= MOD)
                {
                    c -= MOD;
                }
            }
            pre = digit[i];
        }
        return c;
    }
};

/* string l = "23"; // 3
string r = "28";
int b = 8; */

/* string l = "2"; // 2
string r = "7";
int b = 2; */

/* string l = "1"; // 2
string r = "5";
int b = 2; */

/* string l = "1";  // 3
string r = "13";
int b = 2; */

/* string l = "1"; // 9
string r = "29";
int b = 3; */

string l = "148303515506495308555489341658448750"; // 804554770
string r = "15752306151363429826606076402169906057564908";
int b = 9;

int main()
{
    Solution sol;
    int ans = sol.countNumbers(l, r, b);
    printf("ans = %d\n", ans);
    return 0;
}