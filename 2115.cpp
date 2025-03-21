#include <vector>
#include <unordered_set>
#include <stack>
using namespace std;

class Solution
{
private:
    unordered_map<string, int> recipesMap;
    unordered_set<string> suppliesSet;
    unordered_set<int> canCreate;
    unordered_set<int> expanding;
    bool isCanCreate(vector<vector<string>> &ingredients, string target)
    {
        if (suppliesSet.count(target))
            return true;
        auto targetIndex = recipesMap.find(target);
        if (targetIndex == recipesMap.end() || expanding.count(targetIndex->second))
            return false;
        if (canCreate.count(targetIndex->second))
            return true;
        expanding.insert(targetIndex->second);
        vector<string> targetIngredients = ingredients[targetIndex->second];
        for (int i = 0; i < targetIngredients.size(); i++)
        {
            if (!isCanCreate(ingredients, targetIngredients[i]))
                return false;
        }
        canCreate.insert(targetIndex->second);
        expanding.erase(targetIndex->second);
        return true;
    }

public:
    vector<string> findAllRecipes(vector<string> &recipes,
                                  vector<vector<string>> &ingredients,
                                  vector<string> &supplies)
    {
        int n = recipes.size();
        vector<string> ans;
        for (int i = 0; i < n; i++)
        {
            recipesMap[recipes[i]] = i;
        }
        suppliesSet.insert(supplies.begin(), supplies.end());
        for (int i = 0; i < n; i++)
        {
            if (isCanCreate(ingredients, recipes[i]))
                ans.push_back(recipes[i]);
        }
        return ans;
    }
};

vector<string> recipes = {"bread", "sandwich", "burger"};
vector<vector<string>> ingredients = {{"yeast", "flour"}, {"bread", "meat"}, {"sandwich", "meat", "bread"}};
vector<string> supplies = {"yeast", "flour", "meat"};

int main()
{
    Solution sol;
    vector<string> ans = sol.findAllRecipes(recipes, ingredients, supplies);
    printf("ans = [%s", ans[0].c_str());
    for (int i = 1; i < ans.size(); i++)
    {
        printf(", %s", ans[i].c_str());
    }
    printf("]\n");
    return 0;
}