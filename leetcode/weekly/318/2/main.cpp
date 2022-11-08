#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {11, 4};
    vector<int> costs[2] = {{17,12,10,2,7,2,11,20,8}, {1,2,4,1}};
    int k[2] = {3, 3};
    int candidates[2] = {4, 3};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.totalCost(costs[i], k[i], candidates[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}