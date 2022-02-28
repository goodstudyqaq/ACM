// copy_start_symbol=hello copy_end_symbol=world
#include "../header.h"

// hello
class Solution {
   public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        map<int, int> M;
        for (int i = 0; i < target.size(); i++) {
            M[target[i]] = i;
        }

        int m = arr.size();
        vector<int> res;
        for (int i = 0; i < m; i++) {
            if (!M.count(arr[i])) continue;
            auto it = lower_bound(res.begin(), res.end(), M[arr[i]]);
            if (it == res.end()) {
                res.push_back(M[arr[i]]);
            } else {
                *it = M[arr[i]];
            }
        }
        return m - res.size();
    }
};
// world