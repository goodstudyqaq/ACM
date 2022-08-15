#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {7, 0};
    vector<int> edges[2] = {{1,0,0,0,0,7,7,5}, {2,0,0,2}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.edgeScore(edges[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}