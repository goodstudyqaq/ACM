#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {5, 0, 20};
    string directions[3] = {"RLRSLL", "LLRR", "SSRSSRLLRSLLRSRSSRLRRRRLLRRLSSRR"};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.countCollisions(directions[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}