#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {2, 2};
    vector<int> nums[2] = {{0,1,4,6,7,10}, {4,5,6,7,8,9}};
    int diff[2] = {3, 2};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.arithmeticTriplets(nums[i], diff[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}