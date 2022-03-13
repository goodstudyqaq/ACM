#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {9, -1};
    int n[2] = {6, 3};
    vector<vector<int>> edges[2] = {{{0, 2, 2}, {0, 5, 6}, {1, 0, 3}, {1, 4, 5}, {2, 1, 1}, {2, 3, 3}, {2, 3, 4}, {3, 4, 2}, {4, 5, 1}}, {{0, 1, 1}, {2, 1, 1}}};
    int src1[2] = {0, 0};
    int src2[2] = {1, 1};
    int dest[2] = {5, 2};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.minimumWeight(n[i], edges[i], src1[i], src2[i], dest[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}