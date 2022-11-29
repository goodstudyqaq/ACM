#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, 1};
    vector<int> nums[2] = {{3,2,1,4,5}, {2,3,1}};
    int k[2] = {4, 3};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.countSubarrays(nums[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}