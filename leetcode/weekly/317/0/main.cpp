#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {9, 0};
    vector<int> nums[2] = {{1,3,6,10,12,15}, {1,2,4,7,10}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.averageValue(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}