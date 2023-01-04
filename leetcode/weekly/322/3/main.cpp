#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {4, -1};
    int n[2] = {6, 3};
    vector<vector<int>> edges[2] = {{{1,2},{1,4},{1,5},{2,6},{2,3},{4,6}}, {{1,2},{2,3},{3,1}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.magnificentSets(n[i], edges[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}