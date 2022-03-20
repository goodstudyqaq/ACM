/*
Code generated by https://github.com/goodStudyTnT/leetcode-tester
*/

#if __has_include("../../utils/cpp/help.h")
#include "../../utils/cpp/help.h"
#endif

class Solution {
   public:
    int halveArray(vector<int>& nums) {
        int n = nums.size();

        double res = 0;
        priority_queue<double> Q;
        for (int i = 0; i < n; i++) {
            res += nums[i];
            Q.push(nums[i]);
        }
        debug(res);

        double aim = 1.0 * res / 2.0;
        int ans = 0;
        while (res > aim) {
            debug(res);
            ans++;
            double tmp = Q.top();
            Q.pop();
            tmp /= 2;
            res -= tmp;
            Q.push(tmp);
        }
        return ans;
    }
};