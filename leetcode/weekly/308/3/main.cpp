#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<vector<int>> res[2] = {{{3,0,0},{0,0,1},{0,2,0}}, {}};
    int k[2] = {3, 3};
    vector<vector<int>> rowConditions[2] = {{{1,2},{3,2}}, {{1,2},{2,3},{3,1},{2,3}}};
    vector<vector<int>> colConditions[2] = {{{2,1},{3,2}}, {{2,1}}};
    for (int i = 0; i < 2; i++) {
        vector<vector<int>> my_ans = sol.buildMatrix(k[i], rowConditions[i], colConditions[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}