#include "../../header.h"
class Solution {
   public:
    vector<int> sortEvenOdd(vector<int>& nums) {
        vector<int> num[2];
        for (int i = 0; i < nums.size(); i++) {
            num[i % 2].push_back(nums[i]);
        }
        sort(num[0].begin(), num[0].end());
        sort(num[1].begin(), num[1].end());
        reverse(num[1].begin(), num[1].end());
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            if (i / 2 < num[i % 2].size())
                ans.push_back(num[i % 2][i / 2]);
        }
        return ans;
    }
};