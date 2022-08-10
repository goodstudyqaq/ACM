#include "./solution.h"

int main() {
    Solution sol = Solution();
    bool res[2] = {true, false};
    vector<int> nums[2] = {{4,4,4,5,6}, {1,1,1,2}};
    for (int i = 0; i < 2; i++) {
        bool my_ans = sol.validPartition(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}