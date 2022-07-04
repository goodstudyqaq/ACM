#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {9, 0};
    vector<int> nums[2] = {{1,5,5,4,11}, {5,5,2,4,4,2}};
    vector<vector<int>> edges[2] = {{{0,1},{1,2},{1,3},{3,4}}, {{0,1},{1,2},{5,2},{4,3},{1,3}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minimumScore(nums[i], edges[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}