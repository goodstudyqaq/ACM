#include "./solution.h"

int main() {
    Solution sol = Solution();
    string res[2] = {"there are $0.50 $1.00 and 5$ candies in the shop", "1 2 $0.00 4 $0.00 $0.00 7 8$ $0.00 $10$"};
    string sentence[2] = {"there are $1 $2 and 5$ candies in the shop", "1 2 $3 4 $5 $6 7 8$ $9 $10$"};
    int discount[2] = {50, 100};
    for (int i = 0; i < 2; i++) {
        string my_ans = sol.discountPrices(sentence[i], discount[i]);
        compare_result(to_string(i), my_ans, res[i]);
    }
    return 0;
}