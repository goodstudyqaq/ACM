#include "./solution.h"

int main() {
    Solution sol = Solution();
    bool res[2] = {true, false};
    vector<vector<char>> grid[2] = {{{"(","(","("},{")","(",")"},{"(","(",")"},{"(","(",")"}}, {{")",")"},{"(","("}}};
    for (int i = 0; i < 2; i++) {
        bool my_ans = sol.hasValidPath(grid[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}