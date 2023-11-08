#include <iostream>
// #include<bits/stdc++.h>
#include <cmath>
#include <cstdio>
// #include<cstdlib>
#include <algorithm>
#include <cstring>
// #include<queue>
#include <vector>
// #include<set>
// #include<climits>
// #include<map>
using namespace std;
typedef long long LL;
#define N 100010
#define pi 3.1415926535
#define inf 0x3f3f3f3f

const int maxn = 1e6 + 5;
char s[maxn], ss[maxn * 2], t[maxn], s_rev[maxn];
LL pre[maxn * 2];
int lens, lent, p[maxn * 2];

int init() {
    ss[0] = '$';
    ss[1] = '#';
    int lenss = 2;
    for (int i = 0; i < lens; i++) {
        ss[lenss++] = s[i];
        ss[lenss++] = '#';
    }
    ss[lenss] = '\0';
    return lenss;
}

void manacher() {
    int lenss = init();
    int id, mx = 0;
    for (int i = 1; i < lenss; i++) {
        if (i < mx) {
            p[i] = min(p[2 * id - i], mx - i);
        } else {
            p[i] = 1;
        }
        while (ss[i - p[i]] == ss[i + p[i]]) p[i]++;
        if (mx < i + p[i]) {
            id = i;
            mx = i + p[i];
        }
    }
}

int nxt[maxn], ex[maxn];  // ex数组即为extend数组
// 预处理计算next数组
void GETNEXT(char *str) {
    int i = 0, j, po, len = strlen(str);
    nxt[0] = len;                                // 初始化next[0]
    while (str[i] == str[i + 1] && i + 1 < len)  // 计算next[1]
        i++;
    nxt[1] = i;
    po = 1;  // 初始化po的位置
    for (i = 2; i < len; i++) {
        if (nxt[i - po] + i < nxt[po] + po)  // 第一种情况，可以直接得到next[i]的值
            nxt[i] = nxt[i - po];
        else  // 第二种情况，要继续匹配才能得到next[i]的值
        {
            j = nxt[po] + po - i;
            if (j < 0) j = 0;                            // 如果i>po+nxt[po],则要从头开始匹配
            while (i + j < len && str[j] == str[j + i])  // 计算next[i]
                j++;
            nxt[i] = j;
            po = i;  // 更新po的位置
        }
    }
}
// 计算extend数组
void EXKMP(char *s1, char *s2) {
    int i = 0, j, po, len = strlen(s1), l2 = strlen(s2);
    GETNEXT(s2);                                 // 计算子串的next数组
    while (s1[i] == s2[i] && i < l2 && i < len)  // 计算ex[0]
        i++;
    ex[0] = i;
    po = 0;  // 初始化po的位置
    for (i = 1; i < len; i++) {
        if (nxt[i - po] + i < ex[po] + po)  // 第一种情况，直接可以得到ex[i]的值
            ex[i] = nxt[i - po];
        else  // 第二种情况，要继续匹配才能得到ex[i]的值
        {
            j = ex[po] + po - i;
            if (j < 0) j = 0;                                    // 如果i>ex[po]+po则要从头开始匹配
            while (i + j < len && j < l2 && s1[j + i] == s2[j])  // 计算ex[i]
                j++;
            ex[i] = j;
            po = i;  // 更新po的位置
        }
    }
}

int main() {
    freopen("data.in", "r", stdin);
    while (scanf("%s", s) != EOF) {
        scanf("%s", t);
        lens = strlen(s);
        lent = strlen(t);
        for (int i = 0; i <= lens * 2 + 2; i++) {
            pre[i] = 0;
            p[i] = 0;
            ex[i] = 0;
        }
        manacher();
        for (int i = lens * 2; i >= 2; i--) {
            int x = i / 2;
            pre[x]++;
            pre[x - (p[i] / 2)]--;
        }
        for (int i = lens; i >= 1; i--) {
            pre[i] += pre[i + 1];
        }

        for (int i = 0; i <= lens; i++) {
            s_rev[i] = s[lens - 1 - i];
        }
        EXKMP(s_rev, t);
        LL ans = 0;
        /*for(int i = 1; i <= lens; i++){
            cout<<pre[i]<<" "<<ex[i]<<endl;
        }*/
        for (int i = 1; i <= lens; i++) {
            // if(ex[lens - i + 1])
            ans += 1LL * ex[lens - i + 1] * pre[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}