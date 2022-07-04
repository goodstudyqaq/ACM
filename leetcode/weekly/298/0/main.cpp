#include "./solution.h"

int main() {
    Solution sol = Solution();
    string res[3] = {"E", "R", ""};
    string s[3] = {"lEeTcOdE", "arRAzFif", "AbCdEfGhIjK"};
    for (int i = 0; i < 3; i++) {
        string my_ans = sol.greatestLetter(s[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}