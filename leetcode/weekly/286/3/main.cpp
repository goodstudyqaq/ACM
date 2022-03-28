#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {101, 706};
    vector<vector<int>> piles[2] = {{{1,100,3},{7,8,9}}, {{100},{100},{100},{100},{100},{100},{1,1,1,1,1,1,700}}};
    int k[2] = {2, 7};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.maxValueOfCoins(piles[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}