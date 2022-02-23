// copy_start_symbol=hello copy_end_symbol=world
#include "../../header.h"

// hello
class Solution {
   public:
    long long coutPairs(vector<int>& nums, int k) {
        int n = nums.size();

        const int maxn = 1e5;
        vector<int> sum(maxn + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            sum[nums[i]]++;
        }

        for (int i = 1; i <= maxn; i++) {
            for (int j = 2; 1LL * i * j <= maxn; j++) {
                sum[i] += sum[i * j];
            }
        }

        long long ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            int g = __gcd(nums[i], k);
            int need = k / g;
            ans += sum[need];
        }

        int ans2 = 0;
        for (int i = 0; i < nums.size(); i++) {
            long long tmp = nums[i] * nums[i];
            if (tmp % k == 0) ans2++;
        }
        return (ans - ans2) / 2 + ans2;
    }
};

// world