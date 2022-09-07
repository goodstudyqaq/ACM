#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, 0};
    int startPos[2] = {1, 2};
    int endPos[2] = {2, 5};
    int k[2] = {3, 10};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.numberOfWays(startPos[i], endPos[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}