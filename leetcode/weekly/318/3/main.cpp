#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {4, 2};
    vector<int> robot[2] = {{0,4,6}, {1,-1}};
    vector<vector<int>> factory[2] = {{{2,2},{6,2}}, {{-2,1},{2,1}}};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.minimumTotalDistance(robot[i], factory[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}