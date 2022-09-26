#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {6, 7, 1};
    vector<int> vals[3] = {{1,3,2,1,3}, {1,1,2,2,3}, {1}};
    vector<vector<int>> edges[3] = {{{0,1},{0,2},{2,3},{2,4}}, {{0,1},{1,2},{2,3},{2,4}}, {}};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.numberOfGoodPaths(vals[i], edges[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}