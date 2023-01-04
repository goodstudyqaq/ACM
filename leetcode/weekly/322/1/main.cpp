#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[3] = {22, 12, -1};
    vector<int> skill[3] = {{3,2,5,1,3,4}, {3,4}, {1,1,2,3}};
    for (int i = 0; i < 3; i++) {
        long long my_ans = sol.dividePlayers(skill[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}