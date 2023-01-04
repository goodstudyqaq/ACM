#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {6, 0, 2};
    vector<int> nums[3] = {{1,2,3,4}, {3,3,3}, {6,6}};
    int k[3] = {4, 4, 2};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.countPartitions(nums[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}