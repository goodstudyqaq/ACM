// copy_start_symbol=hello copy_end_symbol=world
#include "../../header.h"
//hello
vector<int> M[2];
vector<int> f[2];

bool cmp1(int a, int b) {
    return M[0][a] > M[0][b];
}

bool cmp2(int a, int b) {
    return M[1][a] > M[1][b];
}
class Solution {
   public:
    int minimumOperations(vector<int>& nums) {
        M[0].clear();
        M[1].clear();
        M[0].resize(100001, 0);
        M[1].resize(100001, 0);
        int n = nums.size();
        if (n == 1) {
            return 0;
        }
        if (n == 2) {
            return nums[0] == nums[1];
        }

        for (int i = 0; i < n; i++) {
            M[i % 2][nums[i]]++;
        }
        f[0].clear();
        f[1].clear();
        for (int i = 0; i < M[0].size(); i++) {
            if (M[0][i])
                f[0].emplace_back(i);
        }
        for (int i = 0; i < M[1].size(); i++) {
            if (M[1][i])
                f[1].emplace_back(i);
        }

        sort(f[0].begin(), f[0].end(), cmp1);
        sort(f[1].begin(), f[1].end(), cmp2);

        int res = n - 2;
        for (int i = 0; i < f[0].size() && i < 2; i++) {
            res = min(res, n - M[0][f[0][i]]);
            for (int j = 0; j < f[1].size() && j < 2; j++) {
                res = min(res, n - M[1][f[1][j]]);
                if (f[0][i] == f[1][j]) continue;
                res = min(res, n - M[0][f[0][i]] - M[1][f[1][j]]);
            }
        }
        return res;
    }
};
//world