#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {6, 1};
    vector<int> nums[2] = {{1,13,10,12,31}, {2,2,2}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.countDistinctIntegers(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}