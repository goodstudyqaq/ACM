#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, 0};
    vector<int> nums[2] = {{4,4,2,4,3}, {1,1,1,1,1}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.unequalTriplets(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}