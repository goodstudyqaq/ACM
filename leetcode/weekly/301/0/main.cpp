#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {4, 7, 5};
    vector<int> amount[3] = {{1,4,2}, {5,4,4}, {5,0,0}};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.fillCups(amount[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}