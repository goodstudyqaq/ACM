#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[3] = {{3,1}, {1,0}, {0,1}};
    vector<int> nums[3] = {{1,3,2,1,3,2,2}, {1,1}, {0}};
    for (int i = 0; i < 3; i++) {
        vector<int> my_ans = sol.numberOfPairs(nums[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}