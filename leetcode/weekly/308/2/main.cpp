#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {21, 37};
    vector<string> garbage[2] = {{"G","P","GP","GG"}, {"MMM","PGM","GP"}};
    vector<int> travel[2] = {{2,4,3}, {3,10}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.garbageCollection(garbage[i], travel[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}