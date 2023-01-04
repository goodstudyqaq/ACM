#include "./solution.h"

void test0(){
    int n[1] = {10};
    int size[7] = {1, 1, 1, 3, 1, 1, 10};
    int mID[7] = {1, 2, 3, 4, 1, 1, 2};
    int mID0[3] = {2, 1, 7};
    Allocator *obj = new Allocator(n[0]);
    int res0 = obj->allocate(size[0], mID[0]);
    int ans0 = 0;
    compare_result("0-0", res0, ans0);
    int res1 = obj->allocate(size[1], mID[1]);
    int ans1 = 1;
    compare_result("0-1", res1, ans1);
    int res2 = obj->allocate(size[2], mID[2]);
    int ans2 = 2;
    compare_result("0-2", res2, ans2);
    int res3 = obj->free(mID0[0]);
    int ans3 = 1;
    compare_result("0-3", res3, ans3);
    int res4 = obj->allocate(size[3], mID[3]);
    int ans4 = 3;
    compare_result("0-4", res4, ans4);
    int res5 = obj->allocate(size[4], mID[4]);
    int ans5 = 1;
    compare_result("0-5", res5, ans5);
    int res6 = obj->allocate(size[5], mID[5]);
    int ans6 = 6;
    compare_result("0-6", res6, ans6);
    int res7 = obj->free(mID0[1]);
    int ans7 = 3;
    compare_result("0-7", res7, ans7);
    int res8 = obj->allocate(size[6], mID[6]);
    int ans8 = -1;
    compare_result("0-8", res8, ans8);
    int res9 = obj->free(mID0[2]);
    int ans9 = 0;
    compare_result("0-9", res9, ans9);
}

int main() {
    test0();
    return 0;
}
