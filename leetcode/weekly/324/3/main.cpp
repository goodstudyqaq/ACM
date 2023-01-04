#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{4,5,3}, {2}};
    int n[2] = {3, 2};
    vector<vector<int>> queries[2] = {{{5,3},{4,7},{2,3}}, {{1,2}}};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.cycleLengthQueries(n[i], queries[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}