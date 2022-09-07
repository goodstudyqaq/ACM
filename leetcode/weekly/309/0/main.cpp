#include "./solution.h"

int main() {
    Solution sol = Solution();
    bool res[2] = {true, false};
    string s[2] = {"abaccb", "aa"};
    vector<int> distance[2] = {{1,3,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    for (int i = 0; i < 2; i++) {
        bool my_ans = sol.checkDistances(s[i], distance[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}