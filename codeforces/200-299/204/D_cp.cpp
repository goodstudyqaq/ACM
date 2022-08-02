#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define REP(i, n) for ((i) = 0; (i) < (int)(n); (i)++)
#define foreach(c, itr) for (__typeof((c).begin()) itr = (c).begin(); itr != (c).end(); itr++)

typedef long long ll;
#define MOD 1000000007ll

int N, K;
string s;

int Bsum[1000010], Wsum[1000010];
ll leftmost[1000010], Bfree[1000010], rightmost[1000010], Wfree[1000010];

void dp_left(void) {
    int i;

    Bfree[0] = 1;

    for (i = 1; i <= N; i++) {
        if (i == 7) {
            cout << Wsum[i] << "ttt" << Wsum[i - K] << endl;
        }
        if (i >= K && Wsum[i] - Wsum[i - K] == 0) {
            cout << i << endl;
            if (i == K || s[i - K - 1] != 'B') {
                leftmost[i] = Bfree[max(i - K - 1, 0)];
            };
        }
        ll tmp = Bfree[i - 1];
        if (s[i - 1] == 'X') tmp = tmp * 2 % MOD;
        tmp = (tmp - leftmost[i] + MOD) % MOD;
        Bfree[i] = tmp;
    }
}

void dp_right(void) {
    int i;

    Wfree[N] = 1;

    for (i = N - 1; i >= 0; i--) {
        if (i <= N - K && Bsum[i + K] - Bsum[i] == 0)
            if (i == N - K || s[i + K] != 'W') rightmost[i] = Wfree[min(i + K + 1, N)];
        ll tmp = Wfree[i + 1];
        if (s[i] == 'X') tmp = tmp * 2 % MOD;
        tmp = (tmp - rightmost[i] + MOD) % MOD;
        Wfree[i] = tmp;
    }
}

int main(void) {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int i;

    cin >> N >> K >> s;
    REP(i, N)
    Bsum[i + 1] = Bsum[i] + ((s[i] == 'B') ? 1 : 0);
    REP(i, N)
    Wsum[i + 1] = Wsum[i] + ((s[i] == 'W') ? 1 : 0);

    dp_left();
    dp_right();

    ll ans = 0;

    ll two = 1;

    for (int i = 0; i <= N; i++) {
        cout << leftmost[i] << ' ';
    }
    cout << endl;

    for (int i = 0; i <= N; i++) {
        cout << Bfree[i] << ' ';
    }
    cout << endl;

    for (int i = 0; i <= N; i++) {
        cout << rightmost[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i <= N; i++) {
        cout << Wfree[i] << ' ';
    }
    cout << endl;

    for (i = N - 1; i >= 0; i--) {
        if (s[i] == 'X') two = two * 2 % MOD;
        ll containW = (two - Wfree[i] + MOD) % MOD;
        ans = (ans + leftmost[i] * containW) % MOD;
    }

    cout << ans << endl;

    return 0;
}