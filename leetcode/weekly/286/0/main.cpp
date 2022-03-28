#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<vector<int>> res[2] = {{{1,3},{4,6}}, {{3},{}}};
    vector<int> nums1[2] = {{1,2,3}, {1,2,3,3}};
    vector<int> nums2[2] = {{2,4,6}, {1,1,2,2}};
    for (int i = 0; i < 2; i++) {
        vector<vector<int>> my_ans = sol.findDifference(nums1[i], nums2[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}