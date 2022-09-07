#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, 1};
    vector<int> nums[2] = {{1,3,8,48,10}, {3,1,5,11,13}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.longestNiceSubarray(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}