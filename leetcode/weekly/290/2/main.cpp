#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{2,1}, {1,3}};
    vector<vector<int>> rectangles[2] = {{{1,2},{2,3},{2,5}}, {{1,1},{2,2},{3,3}}};
    vector<vector<int>> points[2] = {{{2,1},{1,4}}, {{1,3},{1,1}}};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.countRectangles(rectangles[i], points[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}