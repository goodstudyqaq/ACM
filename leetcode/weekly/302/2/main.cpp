#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{2,2,1,0}, {3,0}};
    vector<string> nums[2] = {{"102","473","251","814"}, {"24","37","96","04"}};
    vector<vector<int>> queries[2] = {{{1,1},{2,3},{4,2},{1,2}}, {{2,1},{2,2}}};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.smallestTrimmedNumbers(nums[i], queries[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}