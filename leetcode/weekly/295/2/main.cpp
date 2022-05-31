#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {6, 0};
    vector<int> nums[2] = {{10, 1, 2, 3, 4, 5, 6, 1, 2, 3}, {4, 5, 7, 7, 13}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.totalSteps(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}