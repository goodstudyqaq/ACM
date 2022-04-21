#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {4, -1};
    vector<int> tasks[2] = {{2,2,3,3,2,4,4,4,4,4}, {2,3,3}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minimumRounds(tasks[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}