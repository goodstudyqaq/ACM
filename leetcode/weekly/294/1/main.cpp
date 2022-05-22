#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, 3};
    vector<int> capacity[2] = {{2,3,4,5}, {10,2,2}};
    vector<int> rocks[2] = {{1,2,4,4}, {2,2,0}};
    int additionalRocks[2] = {2, 100};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.maximumBags(capacity[i], rocks[i], additionalRocks[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}