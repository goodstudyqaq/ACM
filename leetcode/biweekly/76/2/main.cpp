#include "./solution.h"

void test0(){
    vector<int> banknotesCount[2] = {{0, 0, 1, 2, 1}, {0, 1, 0, 1, 1}};
    int amount[3] = {600, 600, 550};
    ATM *obj = new ATM();
    obj->deposit(banknotesCount[0]);
    vector<int> res0 = obj->withdraw(amount[0]);
    vector<int> ans0 = ['0', '0', '1', '0', '1'];
    compare_result("0-0", res0, ans0);
    obj->deposit(banknotesCount[1]);
    vector<int> res1 = obj->withdraw(amount[1]);
    vector<int> ans1 = ['-1'];
    compare_result("0-1", res1, ans1);
    vector<int> res2 = obj->withdraw(amount[2]);
    vector<int> ans2 = ['0', '1', '0', '0', '1'];
    compare_result("0-2", res2, ans2);
}

int main() {
    test0();
    return 0;
}
