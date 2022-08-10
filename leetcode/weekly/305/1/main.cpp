#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {4, 3};
    int n[2] = {7, 7};
    vector<vector<int>> edges[2] = {{{0,1},{1,2},{3,1},{4,0},{0,5},{5,6}}, {{0,1},{0,2},{0,5},{0,4},{3,2},{6,5}}};
    vector<int> restricted[2] = {{4,5}, {4,2,1}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.reachableNodes(n[i], edges[i], restricted[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}