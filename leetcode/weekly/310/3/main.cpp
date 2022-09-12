#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {5, 4, 1};
    vector<int> nums[3] = {{4,2,1,4,3,4,5,8,15}, {7,4,5,1,8,12,4,7}, {1,5}};
    int k[3] = {3, 5, 1};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.lengthOfLIS(nums[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}