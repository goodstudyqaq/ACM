#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{2,3}, {}};
    vector<int> nums[2] = {{2,1,1,1,3,4,1}, {2,1,1,2}};
    int k[2] = {2, 2};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.goodIndices(nums[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}