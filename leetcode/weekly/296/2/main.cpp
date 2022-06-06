#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{3,2,7,1}, {2,1}};
    vector<int> nums[2] = {{1,2,4,6}, {1,2}};
    vector<vector<int>> operations[2] = {{{1,3},{4,7},{6,1}}, {{1,3},{2,1},{3,2}}};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.arrayChange(nums[i], operations[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}