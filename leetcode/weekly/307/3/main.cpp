#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {2, 10};
    vector<int> nums[2] = {{2,4,-2}, {1,-2,3,4,-10,12}};
    int k[2] = {5, 16};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.kSum(nums[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}