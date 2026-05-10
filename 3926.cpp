#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

class Solution
{
public:
    vector<int> countWordOccurrences(vector<string> &chunks,
                                     vector<string> &queries)
    {
        unordered_map<string, int> mp;
        string a = "";
        for (auto &s : chunks)
        {
            for (auto &c : s)
            {
                if (c >= 'a' && c <= 'z')
                {
                    a += c;
                }
                else if (c == '-')
                {
                    if (a != "")
                    {
                        if (a[a.size() - 1] == '-')
                        {
                            a.pop_back();
                            mp[a]++;
                            a = "";
                        }
                        else
                        {
                            a += c;
                        }
                    }
                }
                else
                {
                    if (a != "")
                    {
                        if (a[a.size() - 1] == '-')
                        {
                            a.pop_back();
                        }
                        mp[a]++;
                        a = "";
                    }
                }
            }
        }
        if (a != "")
        {
            if (a[a.size() - 1] == '-')
            {
                a.pop_back();
            }
            mp[a]++;
        }
        int q = queries.size();
        vector<int> res(q);
        for (int i = 0; i < q; i++)
        {
            res[i] = mp[queries[i]];
        }
        return res;
    }
};

int main()
{
    string problemName = "3926";
    auto begin = jtimer();
    Solution sol;
    ifstream file_in("testcases/" + problemName + "_in.txt");
    ifstream file_out("testcases/" + problemName + "_out.txt");
    bool allPass = true;
    int caseCount = 0;
    int passCount = 0;
    string line_in;
    string line_out;
    while (getline(file_in, line_in))
    {
        auto chunks = jread_vector_string(line_in);
        getline(file_in, line_in);
        auto queries = jread_vector_string(line_in);
        auto res = sol.countWordOccurrences(chunks, queries);
        getline(file_out, line_out);
        auto ans = jread_vector(line_out);
        printf("Case %d", ++caseCount);
        if (res == ans)
        {
            passCount++;
            printf(" %s(PASS)", KGRN);
        }
        else
        {
            printf(" %s(WRONG)", KRED);
            allPass = false;
        }
        printf("\n%s", KNRM);
        jprint(res, "res");
        jprint(ans, "ans");
        printf("\n");
    }
    if (allPass)
    {
        printf("%sALL CORRECT [%d/%d]\n%s", KGRN, passCount, caseCount, KNRM);
    }
    else
    {
        printf("%sWRONG ANSWER [%d/%d]\n%s", KRED, passCount, caseCount, KNRM);
    }
    auto end = jtimer();
    jprint_time(begin, end);
    return 0;
}