#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {4, 1};
    vector<int> nums[2] = {{2,4,3,7,10,6}, {2,4,8,16}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.distinctPrimeFactors(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}