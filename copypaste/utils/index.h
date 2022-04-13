/*
下标计算常用
最好用左闭右开, 好进行总结, 起始位置感觉没必要纠结是 0 还是 1

1.  区间长度
    1. [l, r] = r - l + 1
    2. (l, r] = [l, r) = r - l
    3. (l, r) = r - l - 1
*/

void work(int idx, int n) {
    // idx 是不能包括的下标, 从左边过来就是
    int now = 0;
    while (now < idx) {
        // do sth...
        now++;
    }
    // 从右边过来
    now = n - 1;
    while (now > idx) {
        // do sth ...
        now--;
    }
}
