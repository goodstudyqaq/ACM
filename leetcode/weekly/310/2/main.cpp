#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, 1};
    vector<vector<int>> intervals[2] = {{{5,10},{6,8},{1,5},{2,3},{1,10}}, {{1,3},{5,6},{8,10},{11,13}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minGroups(intervals[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}