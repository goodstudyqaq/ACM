#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {19, 32};
    int m[2] = {3, 4};
    int n[2] = {5, 6};
    vector<vector<int>> prices[2] = {{{1,4,2},{2,2,7},{2,1,3}}, {{3,2,10},{1,4,2},{4,1,3}}};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.sellingWood(m[i], n[i], prices[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}