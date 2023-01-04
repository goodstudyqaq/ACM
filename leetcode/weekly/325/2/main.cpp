#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[3] = {8, 2, 0};
    vector<int> price[3] = {{13,5,1,8,21,2}, {1,3,1}, {7,7,7,7}};
    int k[3] = {3, 2, 2};
    for (int i = 0; i < 3; i++) {
        int my_ans = sol.maximumTastiness(price[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}