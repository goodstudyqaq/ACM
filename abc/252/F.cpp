#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
ll getWPL(vector<ll> &arr) {                              // 对于未建好的霍夫曼树，直接求其 WPL
    priority_queue<ll, vector<ll>, greater<ll>> huffman;  // 小根堆
    int n = arr.size();
    for (int i = 0; i < n; i++) huffman.push(arr[i]);
    ll res = 0;
    for (int i = 0; i < n - 1; i++) {
        ll x = huffman.top();
        huffman.pop();
        ll y = huffman.top();
        huffman.pop();
        ll temp = x + y;
        res += temp;
        huffman.push(temp);
    }
    return res;
}
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    ll len;
    cin >> n >> len;

    vector<ll> a(n);
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if (len > sum) {
        a.push_back(len - sum);
    }
    cout << getWPL(a) << endl;
}