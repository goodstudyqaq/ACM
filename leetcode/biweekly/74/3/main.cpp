#include "./solution.h"

int main() {
    Solution sol = Solution();
    int res[2] = {2, 0};
    string floor[2] = {"10110101", "11111"};
    int numCarpets[2] = {2, 2};
    int carpetLen[2] = {2, 3};
    for (int i = 0; i < 2; i++) {
        int my_ans = sol.minimumWhiteTiles(floor[i], numCarpets[i], carpetLen[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}