#include "./solution.h"

int main() {
    Solution sol = Solution();
    vector<int> res[2] = {{1,2,2,2}, {2,2,1}};
    vector<vector<int>> flowers[2] = {{{1,6},{3,7},{9,12},{4,13}}, {{1,10},{3,3}}};
    vector<int> persons[2] = {{2,3,7,11}, {3,3,2}};
    for (int i = 0; i < 2; i++) {
        vector<int> my_ans = sol.fullBloomFlowers(flowers[i], persons[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}