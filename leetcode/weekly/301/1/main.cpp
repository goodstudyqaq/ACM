#include "./solution.h"

void test0(){
    int num[2] = {2, 1};
    SmallestInfiniteSet *obj = new SmallestInfiniteSet();
    obj->addBack(num[0]);
    int res0 = obj->popSmallest();
    int ans0 = 1;
    compare_result("0-0", res0, ans0);
    int res1 = obj->popSmallest();
    int ans1 = 2;
    compare_result("0-1", res1, ans1);
    int res2 = obj->popSmallest();
    int ans2 = 3;
    compare_result("0-2", res2, ans2);
    obj->addBack(num[1]);
    int res3 = obj->popSmallest();
    int ans3 = 1;
    compare_result("0-3", res3, ans3);
    int res4 = obj->popSmallest();
    int ans4 = 4;
    compare_result("0-4", res4, ans4);
    int res5 = obj->popSmallest();
    int ans5 = 5;
    compare_result("0-5", res5, ans5);
}

int main() {
    test0();
    return 0;
}
