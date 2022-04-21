#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[1] = {42};
    vector<int> scores[1] = {{8,7,1,26}};
    vector<vector<int>> edges[1] = {{{3,1},{1,2},{2,0},{0,3},{2,3},{0,1}}};
    for (int i = 0; i < 1; i++) {
        int my_ans = sol.maximumScore(scores[i], edges[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}