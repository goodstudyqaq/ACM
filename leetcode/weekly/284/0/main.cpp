#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{1,2,3,4,5,6}, {0,1,2,3,4}};
    vector<int> nums[2] = {{3,4,9,1,3,9,5}, {2,2,2,2,2}};
    int key[2] = {9, 2};
    int k[2] = {1, 2};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.findKDistantIndices(nums[i], key[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}