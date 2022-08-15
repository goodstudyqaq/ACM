#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<vector<int>> res[2] = {{{9,9},{8,6}}, {{2,2,2},{2,2,2},{2,2,2}}};
    vector<vector<int>> grid[2] = {{{9,9,8,1},{5,6,2,6},{8,2,6,4},{6,2,2,2}}, {{1,1,1,1,1},{1,1,1,1,1},{1,1,2,1,1},{1,1,1,1,1},{1,1,1,1,1}}};
    for (int i = 0; i < 2; i++) {
        vector<vector<int>> my_ans = sol.largestLocal(grid[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}