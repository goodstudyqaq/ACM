#include "./solution.h"

int main() {
    Solution sol = Solution();
    bool res[3] = {true, true, false};
    int n[3] = {5, 4, 4};
    vector<vector<int>> edges[3] = {{{1,2},{2,3},{3,4},{4,2},{1,4},{2,5}}, {{1,2},{3,4}}, {{1,2},{1,3},{1,4}}};
    for (int i = 0; i < 3; i++) {
        bool my_ans = sol.isPossible(n[i], edges[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}