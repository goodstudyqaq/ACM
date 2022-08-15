#include "./solution.h"

int main() {
    Solution sol = Solution();
    string res[2] = {"123549876", "4321"};
    string pattern[2] = {"IIIDIDDD", "DDD"};
    for (int i = 0; i < 2; i++) {
        string my_ans = sol.smallestNumber(pattern[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}