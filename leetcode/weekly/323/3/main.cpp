#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{5,8,1}, {0}};
    vector<vector<int>> grid[2] = {{{1,2,3},{2,5,7},{3,5,1}}, {{5,2,1},{1,1,2}}};
    vector<int> queries[2] = {{5,6,2}, {3}};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.maxPoints(grid[i], queries[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}