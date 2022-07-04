#include "./solution.h"

int main() {
    Solution sol = Solution();
    bool res[2] = {true, false};
    vector<vector<int>> grid[2] = {{{2,0,0,1},{0,3,1,0},{0,5,2,0},{4,0,0,2}}, {{5,7,0},{0,3,1},{0,5,0}}};
    for (int i = 0; i < 2; i++) {
        bool my_ans = sol.checkXMatrix(grid[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}