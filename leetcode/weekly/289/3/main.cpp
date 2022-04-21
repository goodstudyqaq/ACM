#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3, 3};
    vector<int> parent[2] = {{-1,0,0,1,1,2}, {-1,0,0,0}};
    string s[2] = {"abacbe", "aabc"};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.longestPath(parent[i], s[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}