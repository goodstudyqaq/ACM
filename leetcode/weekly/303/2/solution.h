/*
Code generated by https://github.com/goodStudyTnT/leetcode-tester
*/

#if __has_include("../../utils/cpp/help.h")
#include "../../utils/cpp/help.h"
#endif

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

typedef pair<int, string> psi;

class FoodRatings {
   public:
    int n;
    unordered_map<string, set<psi>> M;
    unordered_map<string, int> M2;
    unordered_map<string, string> M3;

    FoodRatings(vector<string>& f, vector<string>& c, vector<int>& r) {
        n = f.size();
        M.clear();
        M2.clear();
        M3.clear();
        for (int i = 0; i < n; i++) {
            M2[f[i]] = r[i];
            M3[f[i]] = c[i];
            M[c[i]].insert({-r[i], f[i]});
        }
    }

    void changeRating(string food, int newRating) {
        int r = M2[food];
        string c = M3[food];
        M[c].erase({-r, food});
        M2[food] = newRating;
        M[c].insert({-newRating, food});
    }

    string highestRated(string c) {
        auto it = *M[c].begin();
        return it.second;
    }
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */