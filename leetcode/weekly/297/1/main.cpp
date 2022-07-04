#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {17, 6};
    vector<vector<int>> grid[2] = {{{5,3},{4,0},{2,1}}, {{5,1,2},{4,0,3}}};
    vector<vector<int>> moveCost[2] = {{{9,8},{1,5},{10,12},{18,6},{2,4},{14,3}}, {{12,10,15},{20,23,8},{21,7,1},{8,1,13},{9,10,25},{5,3,2}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minPathCost(grid[i], moveCost[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}