#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {4, -1};
    vector<int> cards[2] = {{3,4,2,3,4,7}, {1,0,5,3}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minimumCardPickup(cards[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}