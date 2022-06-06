#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {2, 2, 3};
    vector<int> nums[3] = {{3,6,1,2,5}, {1,2,3}, {2,2,4,5}};
    int k[3] = {2, 1, 0};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.partitionArray(nums[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}