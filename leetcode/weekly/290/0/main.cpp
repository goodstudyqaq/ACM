#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{3,4}, {}};
    vector<vector<int>> nums[2] = {{{3,1,2,4,5},{1,2,3,4},{3,4,5,6}}, {{1,2,3},{4,5,6}}};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.intersection(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}