#include "./solution.h"

int main() {
    Solution sol = Solution();
    bool res[2] = {true, false};
    vector<int> nums[2] = {{3,2,3,2,2,2}, {1,2,3,4}};
    for (int i = 0; i < 2; i++) {
        bool my_ans = sol.divideArray(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}