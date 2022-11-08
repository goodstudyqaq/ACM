#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{1,4,2,0,0,0}, {1,0}};
    vector<int> nums[2] = {{1,2,2,1,1,0}, {0,1}};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.applyOperations(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}