#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {15, 0};
    vector<int> nums[2] = {{1,5,4,2,9,9,9}, {4,4,4}};
    int k[2] = {3, 3};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.maximumSubarraySum(nums[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}