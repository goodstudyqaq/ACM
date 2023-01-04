#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {8, 10};
    vector<vector<int>> grid[2] = {{{1,2,4},{3,3,1}}, {{10}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.deleteGreatestValue(grid[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}