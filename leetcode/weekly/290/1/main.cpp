#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {5, 16};
    vector<vector<int>> circles[2] = {{{2,2,1}}, {{2,2,2},{3,4,1}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.countLatticePoints(circles[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}