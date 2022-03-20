#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, 0};
    vector<int> nums[2] = {{2,4,1,1,6,5}, {6,6,5,5,4,1}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.countHillValley(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}