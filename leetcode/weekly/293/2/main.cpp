#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {4, 2};
    vector<int> candidates[2] = {{16,17,71,62,12,24,14}, {8,8}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.largestCombination(candidates[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}