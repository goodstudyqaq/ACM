#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {2, 10};
    vector<int> nums[2] = {{1,3,5,2,7,5}, {1,1,1,1}};
    int minK[2] = {1, 1};
    int maxK[2] = {5, 1};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.countSubarrays(nums[i], minK[i], maxK[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}