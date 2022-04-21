#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, 0};
    vector<vector<int>> grid[2] = {{{23,17,15,3,20},{8,1,20,27,11},{9,4,6,2,21},{40,9,1,10,6},{22,7,4,5,3}}, {{4,3,2},{7,6,1},{8,8,8}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.maxTrailingZeros(grid[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}