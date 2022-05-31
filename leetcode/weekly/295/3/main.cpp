#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {2, 0};
    vector<vector<int>> grid[2] = {{{0, 1, 1}, {1, 1, 0}, {1, 1, 0}}, {{0, 1, 0, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 0, 1, 0}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minimumObstacles(grid[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}