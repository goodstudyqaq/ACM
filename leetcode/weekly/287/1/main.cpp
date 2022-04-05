#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<vector<int>> res[2] = {{{1,2,10},{4,5,7,8}}, {{1,2,5,6},{}}};
    vector<vector<int>> matches[2] = {{{1,3},{2,3},{3,6},{5,6},{5,7},{4,5},{4,8},{4,9},{10,4},{10,9}}, {{2,3},{1,3},{5,4},{6,4}}};
    for (int i = 0; i < 2; i++) {
        vector<vector<int>> my_ans = sol.findWinners(matches[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}