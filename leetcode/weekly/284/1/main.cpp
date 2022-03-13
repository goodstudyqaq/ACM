#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {1, 2};
    int n[2] = {2, 2};
    vector<vector<int>> artifacts[2] = {{{0,0,0,0},{0,1,1,1}}, {{0,0,0,0},{0,1,1,1}}};
    vector<vector<int>> dig[2] = {{{0,0},{0,1}}, {{0,0},{0,1},{1,1}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.digArtifacts(n[i], artifacts[i], dig[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}