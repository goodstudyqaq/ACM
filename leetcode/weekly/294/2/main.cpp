#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, 1};
    vector<vector<int>> stockPrices[2] = {{{1,7},{2,6},{3,5},{4,4},{5,4},{6,3},{7,2},{8,1}}, {{3,4},{1,2},{7,8},{2,3}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minimumLines(stockPrices[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}