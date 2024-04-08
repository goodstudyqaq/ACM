#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1;
    cout << tt << '\n';

    int n = 1000;
    int k = 5000;
    cout << n << " " << k << '\n';
    vector<vector<int>> a(n, vector<int>(n, 0));
    int now = 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            a[i][j] = now++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            cout << a[i][j] << " \n"[j == n - 1];
        }
    }
}