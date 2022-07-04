#include "./solution.h"

int main() {
    Solution sol = Solution();
    long long res[2] = {6, 0};
    vector<string> ideas[2] = {{"coffee","donuts","time","toffee"}, {"lack","back"}};
    for (int i = 0; i < 2; i++) {
        long long my_ans = sol.distinctNames(ideas[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}