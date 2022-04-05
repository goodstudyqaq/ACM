#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {8, 5};
    vector<int> nums[2] = {{1,2,3,4,5}, {5}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.triangularSum(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}