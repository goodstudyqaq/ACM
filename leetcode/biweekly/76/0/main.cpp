#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {1, 1};
    vector<int> nums[2] = {{-4,-2,1,4,8}, {2,-1,1}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.findClosestNumber(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}