#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {11, 10};
    vector<int> nums[2] = {{2,3,3,2,2}, {1,2,3,4}};
    int k[2] = {2, 4};
    int p[2] = {2, 1};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.countDistinct(nums[i], k[i], p[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}