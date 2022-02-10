// copy_start_symbol=hello copy_end_symbol=world
#include "../header.h"

// hello

class Solution {
   public:
    vector<vector<int>> mp;
    vector<int> peopleIndexes(vector<vector<string>>& fav) {
        int n = fav.size();
        mp.clear();
        mp.resize(n, vector<int>(n, 0));

        map<string, vector<int>> M;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < fav[i].size(); j++) {
                M[fav[i][j]].push_back(i);
            }
        }

        for (auto it : M) {
            auto it2 = it.second;
            for (int i = 0; i < it2.size(); i++) {
                for (int j = i + 1; j < it2.size(); j++) {
                    mp[it2[i]][it2[j]]++;
                    mp[it2[j]][it2[i]]++;
                }
            }
        }
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            int sz = fav[i].size();
            bool f = true;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (mp[i][j] == sz) {
                    f = false;
                    break;
                }
            }
            if (f) ans.push_back(i);
        }
        return ans;
    }
};
// world