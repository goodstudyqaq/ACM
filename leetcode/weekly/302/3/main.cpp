#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {2, -1};
    vector<int> nums[2] = {{2,3,2,4,3}, {4,3,6}};
    vector<int> numsDivide[2] = {{9,6,9,3,15}, {8,2,6,10}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minOperations(nums[i], numsDivide[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}