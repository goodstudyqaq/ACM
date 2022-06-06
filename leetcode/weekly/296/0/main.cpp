#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {1, 3};
    vector<int> nums[2] = {{1,3,5,2,4,8,2,2}, {3}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minMaxGame(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}