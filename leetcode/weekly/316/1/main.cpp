#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {4, 0};
    vector<int> nums[2] = {{9,3,1,2,6,3}, {4}};
    int k[2] = {3, 7};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.subarrayGCD(nums[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}