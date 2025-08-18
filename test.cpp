#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif


struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;


int floatFloat2Int(unsigned uf) {
  int sign = (uf >> 31) & 1;
  int exp = (uf >> 23) & 0xff;
  int fra = uf ^ (sign << 31) ^ (exp << 23);
  int inf = 0x80 << 24;
  int bias = 127;
  exp -= bias;
  debug(exp);
  if (exp < 0) {
    return 0;
  } else if(exp == 0) {
    return 1 + (sign << 31);
  } else if (exp > 31) {
    return inf;
  } else if (exp == 31) {
    if (sign == 1 && fra == 0) {
      return 1 << 31;
    } else {
      return inf;
    }
  } else if (exp <= 23) {
    fra += 1 << 23;
    return (fra >> (23 - exp)) + (sign << 31);
  } else {
    fra += 1 << 23;
    return (fra << (exp - 23)) + (sign << 31);
  }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
  debug(floatFloat2Int(0xbf800000));


}
