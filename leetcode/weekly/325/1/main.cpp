#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {8, -1};
    string s[2] = {"aabaaaacaabc", "a"};
    int k[2] = {2, 1};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.takeCharacters(s[i], k[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}