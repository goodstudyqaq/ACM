#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {5, 0};
    vector<int> nums[2] = {{1,2,3,1}, {5,1,1}};
    int k[2] = {3, 10};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.countExcellentPairs(nums[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}