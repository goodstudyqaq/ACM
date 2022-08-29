#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{2,3,4}, {0}};
    vector<int> nums[2] = {{4,5,2,1}, {2,3,4,5}};
    vector<int> queries[2] = {{3,10,21}, {1}};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.answerQueries(nums[i], queries[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}