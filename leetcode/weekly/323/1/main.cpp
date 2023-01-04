#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, -1};
    vector<int> nums[2] = {{4,3,6,16,8,2}, {2,3,5,6,7}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.longestSquareStreak(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}