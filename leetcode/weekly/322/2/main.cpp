#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {5, 2};
    int n[2] = {4, 4};
    vector<vector<int>> roads[2] = {{{1,2,9},{2,3,6},{2,4,5},{1,4,7}}, {{1,2,2},{1,3,4},{3,4,7}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minScore(n[i], roads[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}