#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int rest = 500;

int inner_string[200005] = {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1};
int ans_len = 18;
int curpos = 1;

int record[200005];
int top = 0;

void show() {
    for (int i = 1; i <= ans_len; ++i) {
        printf ("%d%c", inner_string[i], " \n"[i == ans_len]);
    }
    for (int i = 1; i <= ans_len; ++i) {
        printf ("%c%c", " ^"[i == curpos],  " \n"[i == ans_len]);
    }
    printf ("\n");
}

int move_right() {
    --rest;
    printf ("? right\n");
    fflush (stdout);
    int x = 0;
#ifdef LOCAL
    ++curpos;
    if (curpos > ans_len) {
        curpos = 1;
    }
    x = inner_string[curpos];
//    show();
#endif // LOCAL
#ifndef LOCAL
    scanf ("%d", &x);
#endif // LOCAL
    record[++top] = x;
    return x;
}

int flip() {
    --rest;
    printf ("? flip\n");
    fflush (stdout);
    int x = 0;
#ifdef LOCAL
    inner_string[curpos] = 1 - inner_string[curpos];
    x = inner_string[curpos];
//    show();
#endif // LOCAL
#ifndef LOCAL
    scanf ("%d", &x);
#endif // LOCAL
    record[top] = x;
    return x;
}

void show_pattern (ll pattern, int len) {
    printf ("pattern=");
    for (int i = 1; i <= len; ++i) {
        int x = (pattern >> i) & 1;
        printf ("%d ", x);

    }
    printf ("\n");
}

void show_record () {
    printf ("record=");
    for (int i = 1; i <= top; ++i) {
        printf ("%d ", record[i]);

    }
    printf ("\n");
}

bool check (int guess_len) {
//    printf ("check, guess=%d\n", guess_len);
    ll pattern = ( (1LL * rand()) << 12) ^ ( (1LL * rand()));
//    show_pattern (pattern, guess_len);
    for (int i = 1; i <= guess_len; ++i) {
        int res = move_right();
//        printf ("res=%d\n", res);
        if (record[top] != ( (pattern >> i) & 1)) {
            flip();
        }
    }
//    show_record();
    for (int i = 1; i <= guess_len; ++i) {
        move_right();
//        show_record();
        if (record[top] != ( (pattern >> i) & 1)) {
            return false;
        }
    }
    return true;
}

int check2 () {
//    puts ("!!!!!");
    ll pattern = ( (1LL * rand()) << 12) ^ ( (1LL * rand()));
    const int LEN = 18;
//    show_pattern (pattern, LEN);
    for (int i = 1; i <= LEN; ++i) {
        move_right();
        if (record[top] != ( (pattern >> i) & 1)) {
            flip();
        }
    }
    int cnt = 0;
    for (int i = 1; ; ++i) {
        move_right();
        ++cnt;
        bool ok = 1;
        for (int j = 1; j <= LEN; ++j) {
            if (record[top - LEN + j] != ( (pattern >> j) & 1)) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            return cnt;
//            printf ("! %d\n", cnt);
//            fflush (stdout);
//            return;
        }
    }
}

int main() {
    srand(time(0));
#ifdef LOCAL
    freopen ("A.in", "r", stdin);
#endif // LOCAL

    // 先走3步，把灯关掉
    // 000
    // 然后第4步回到可能的起点，如果是0，则开灯，否则返回
    // 0001
    // 或者可能是
    // 100
    // 然后走3个格子看看是不是，如果是的话则猜测列车的长度是3，否则的话大概花了2n否决一个答案
    // 如果是的话，则秘密随机翻转一位，然后再走3格检验
    // 如果检验成功则相信，重复进行三次，大概花费20的代价确定是3，否则在20以内知道是4
    // 500大概能检验十多个长度。

    // 根据这个方法检验，列车长度应该为x
    // 生成一个密码，然后把长度为x的灯设置为这个密码，消耗2*x
    // 然后不断往前走，直到遇到这个密码，消耗一圈的长度

    int x = 0;
    scanf ("%d", &x);
    top = 0;
    record[++top] = x;

    int guess_len = 3;

    while (rest >= 3 * guess_len + 30) {
        if (check (guess_len) == false) {
            ++guess_len;
        }
//        if (guess_len == ans_len) {
//            printf ("rest=%d\n", rest);
//        }
    }

    int cnt = guess_len;

    if (guess_len > 20) {
        cnt = check2();
    }
    printf ("! %d\n", cnt);
    fflush (stdout);


    int cost = 500 - rest;
    int cost_lim = 3 * cnt + 500;
//    printf ("cost=%d, lim=%d\n", cost, cost_lim);
    return 0;
}
