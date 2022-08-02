/*
n个数，要求选k个数，满足这k个数相与等于0，输出方案个数%1e9+7
*/
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 1e6 + 5;
const int mod = 1e9 + 7;
int a[maxn];
int f[maxn * 2];

long long quick(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b % 2) {
			res = res * a % mod;
		}
		a = a * a % mod;
		b /= 2;
	}
	return res;
}

int main() {
	// freopen("data.in", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		f[a[i]]++;
	}
	int mx = (1 << 20);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < mx; j++) {
			if (((j >> i) & 1) == 0) {
				(f[j] += f[j + (1 << i)]) %= mod;
			}
		}
	}

	// for (int i = 0; i < 100; i++) {
	//     cout << i << ' ' << f[i] << endl;
	// }

	for (int i = 0; i < mx; i++) {
		f[i] = quick(2, f[i]);
	}

	long long ans = 0;
	for (int i = 0; i < mx; i++) {
		int x = i;
		int num = 0;
		while (x) {
			if (x % 2) num++;
			x /= 2;
		}
		if (num % 2) {
			ans = ((ans - f[i]) % mod + mod) % mod;
		} else {
			ans = (ans + f[i]) % mod;
		}
	}
	cout << ans << endl;
}