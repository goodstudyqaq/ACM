#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {54, -1};
    vector<int> nums[2] = {{18,43,36,13,7}, {10,12,19,14}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.maximumSum(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}