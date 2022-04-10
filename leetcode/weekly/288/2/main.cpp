#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {20, 216};
    vector<int> nums[2] = {{0,4}, {6,3,3,2}};
    int k[2] = {5, 2};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.maximumProduct(nums[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}