#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {5, 6};
    int n[2] = {6, 4};
    int delay[2] = {2, 1};
    int forget[2] = {4, 3};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.peopleAwareOfSecret(n[i], delay[i], forget[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}