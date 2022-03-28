#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {1, 2};
    vector<int> nums[2] = {{1,1,2,3,5}, {1,1,2,2,3,3}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minDeletion(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}