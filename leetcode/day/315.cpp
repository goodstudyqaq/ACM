// copy_start_symbol=hello copy_end_symbol=world
#include "../header.h"

// hello
#define lowbit(x) x & -x
const int maxn = 2e4 + 5;
int sum[maxn];
void add(int idx) {
    while (idx < maxn) {
        sum[idx]++;
        idx += lowbit(idx);
    }
}
int query(int idx) {
    int res = 0;
    while (idx) {
        res += sum[idx];
        idx -= lowbit(idx);
    }
    return res;
}
const int offset = 1e4 + 1;

class Solution {
   public:
    vector<int> countSmaller(vector<int>& nums) {
        memset(sum, 0, sizeof(sum));
        int n = nums.size();
        vector<int> ans(n);
        for (int i = n - 1; i >= 0; i--) {
            int val = nums[i] + offset;
            ans[i] = query(val);
            add(val);
        }
        return ans;
    }
};

// world