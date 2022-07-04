#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {4, 9};
    int n[2] = {1, 2};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.countHousePlacements(n[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}