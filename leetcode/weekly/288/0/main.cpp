#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {3412, 87655};
    int num[2] = {1234, 65875};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.largestInteger(num[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}