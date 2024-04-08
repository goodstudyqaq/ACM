#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt = 1;
  cout << tt << '\n';
  while (tt--) {
    int n = 1000;
    int k = 5000;
    cout << n << " " << k << '\n';
    for (int i = 0; i < n; i++) {
      int v = 0;
      for (int j = i; j < n; j++) {
        v += n - j;
        cout << v << " \n"[j == n - 1];
      }
    }
  }
  return 0;
}