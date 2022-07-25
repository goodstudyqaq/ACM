#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {1, 3};
    vector<vector<int>> grid[2] = {{{3,2,1},{1,7,6},{2,7,7}}, {{3,1,2,2},{1,4,4,5},{2,4,2,2},{2,4,2,2}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.equalPairs(grid[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}