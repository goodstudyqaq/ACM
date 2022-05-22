#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {44, 213};
    vector<int> strength[2] = {{1,3,1,2}, {5,4,6}};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.totalStrength(strength[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}