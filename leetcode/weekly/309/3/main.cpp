#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {0, 1};
    int n[2] = {2, 3};
    vector<vector<int>> meetings[2] = {{{0,10},{1,5},{2,7},{3,4}}, {{1,20},{2,10},{3,5},{4,9},{6,8}}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.mostBooked(n[i], meetings[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}