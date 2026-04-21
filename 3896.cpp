#include "Jutil.h"
using namespace std;

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

bool isInit=false;
const int U=2e5;
bool prime[U];
void init(){
    memset(prime,1,sizeof(prime));
    prime[1]=0;
    for(int i=2;i*i<U;i++){
        if(prime[i]){
            for(int j=i*2;j<U;j+=i){
                prime[j]=0;
            }
        }
    }
}
class Solution {
public:
    int minOperations(vector<int>& nums) {
        if(!isInit){
            init();
            isInit=true;
        }
        int n=nums.size();
        int res=0;
        for(int i=0;i<n;i+=2){
            while(!prime[nums[i]]){
                nums[i]++;
                res++;
            }
        }
        for(int i=1;i<n;i+=2){
            while(prime[nums[i]]){
                nums[i]++;
                res++;
            }
        }
        return res;
    }
};

int main() {
    string problemName = "3896";
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
        auto res = sol.minOperations(nums);
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