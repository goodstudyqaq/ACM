#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {6, 1, -1};
    int n[3] = {8, 1, 4};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.pivotInteger(n[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}