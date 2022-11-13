#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {4, 0};
    vector<int> nums[2] = {{3,6,2,7,1}, {3}};
    int k[2] = {6, 2};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.subarrayLCM(nums[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}