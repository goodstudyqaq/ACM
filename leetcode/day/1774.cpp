#include "../header.h"
class Solution {
   public:
    vector<int> all;
    vector<int>& _t;
    int _target;

    void dfs(int idx, int now_val) {
        if (idx == _t.size()) {
            all.push_back(now_val);
            return;
        }
        for (int i = 0; i < 3; i++) {
            dfs(idx + 1, now_val + _t[idx] * i);
        }
    }

    int closestCost(vector<int>& b, vector<int>& t, int target) {
        _t = t;
        _target = target;
        all.clear();
        dfs(0, 0);

        int res = -1;
        for (int i = 0; i < b.size(); i++) {
            for (int j = 0; j < all.size(); j++) {
                int tmp = b[i] + all[j];
                if (res == -1 || abs(res - target) > abs(tmp - target)) {
                    res = tmp;
                } else if (abs(res - target) == abs(tmp - target) && tmp < res) {
                    res = tmp;
                }
            }
        }
        return res;
    }
};