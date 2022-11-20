#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[3] = {3, 7, 0};
    vector<vector<int>> roads[3] = {{{0,1},{0,2},{0,3}}, {{3,1},{3,2},{1,0},{0,4},{0,5},{4,6}}, {}};
    int seats[3] = {5, 2, 1};
    for (int i = 0; i < 3; i++) {
        long long my_ans = sol.minimumFuelCost(roads[i], seats[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}