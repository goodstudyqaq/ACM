#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {3, 7, -1};
    vector<int> nums[3] = {{-1,2,-3,3}, {-1,10,6,7,-7,1}, {-10,8,6,7,-2,-3}};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.findMaxK(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}