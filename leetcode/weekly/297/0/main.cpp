#include "./solution.h"

int main() {
    Solution sol = Solution();
    double res[3] = {2.65000, 0.25000, 0.00000};
    vector<vector<int>> brackets[3] = {{{3,50},{7,10},{12,25}}, {{1,0},{4,25},{5,50}}, {{2,50}}};
    int income[3] = {10, 2, 0};
    for (int i = 0; i < 3; i++) {
        double my_ans = sol.calculateTax(brackets[i], income[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}