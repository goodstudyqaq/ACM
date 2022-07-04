#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {8, 3};
    vector<vector<int>> grid[2] = {{{1,1},{3,4}}, {{1},{2}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.countPaths(grid[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}