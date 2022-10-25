#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {8, 0};
    vector<int> nums[2] = {{1,3,5,2}, {2,2,2,2,2}};
    vector<int> cost[2] = {{2,3,1,14}, {4,2,8,1,3}};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.minCost(nums[i], cost[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}