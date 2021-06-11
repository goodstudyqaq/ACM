#include <bits/stdc++.h>

using namespace std;

const int maxn = 4e4;
//时间复杂度O(n)
bool is[maxn];
int prm[maxn], id;
void init() {
    int k = 0;
    memset(is, 1, sizeof(is));
    is[0] = is[1] = 0;
    for (int i = 2; i < maxn; ++i) {
        if (is[i]) prm[k++] = i;
        for (int j = 0; j < k && (i * prm[j] < maxn); ++j) {
            is[i * prm[j]] = 0;
            if (i % prm[j] == 0) break;
        }
    }
    id = k;
}

int work(int val) {
    int res = 0;
    for (int i = 0; i < id; i++) {
        if (val % prm[i] == 0) {
            while (val % prm[i] == 0) {
                res++;
                val /= prm[i];
            }
        }
    }
    if (val != 1) {
        res++;
    }
    return res;
}

int main() {
    init();
    // 	cout << id << endl;
    int T;
    scanf("%d", &T);
    while (T--) {
        int a, b, k;
        scanf("%d %d %d", &a, &b, &k);
        int mx = work(a) + work(b);
        if (k > mx) {
            puts("NO");
            continue;
        } else if (k == 1) {
            if (a == b) {
                puts("NO");
            } else if (a % b == 0 || b % a == 0) {
                puts("YES");
            } else {
                puts("NO");
            }
        } else {
            puts("YES");
        }
    }
    return 0;
}