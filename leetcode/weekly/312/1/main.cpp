#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {2, 1};
    vector<int> nums[2] = {{1,2,3,3,2,2}, {1,2,3,4}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.longestSubarray(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}