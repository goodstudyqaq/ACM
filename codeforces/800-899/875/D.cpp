#include <bits/stdc++.h>

using namespace std;

template < typename A, typename B >
string to_string(pair< A, B > p);

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p);

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p);

string to_string(const string& s) {
	return '"' + s + '"';
}

string to_string(const char* s) {
	return to_string(( string )s);
}

string to_string(bool b) {
	return (b ? "true" : "false");
}

string to_string(vector< bool > v) {
	bool first = true;
	string res = "{";
	for (int i = 0; i < static_cast< int >(v.size()); i++) {
		if (!first) {
			res += ", ";
		}
		first = false;
		res += to_string(v[i]);
	}
	res += "}";
	return res;
}

template < size_t N >
string to_string(bitset< N > v) {
	string res = "";
	for (size_t i = 0; i < N; i++) {
		res += static_cast< char >('0' + v[i]);
	}
	return res;
}

template < typename A >
string to_string(A v) {
	bool first = true;
	string res = "{";
	for (const auto& x : v) {
		if (!first) {
			res += ", ";
		}
		first = false;
		res += to_string(x);
	}
	res += "}";
	return res;
}

template < typename A, typename B >
string to_string(pair< A, B > p) {
	return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p) {
	return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ")";
}

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p) {
	return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ", " + to_string(get< 3 >(p)) + ")";
}

void debug_out() {
	cerr << endl;
}

template < typename Head, typename... Tail >
void debug_out(Head H, Tail... T) {
	cerr << " " << to_string(H);
	debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

const int maxn = 2e5 + 5;
int a[maxn];

int n;
int stc[maxn], scnt;
int lxt[maxn], nxt[maxn];

int val[maxn][20], val2[maxn][20];

void init() {
	for (int i = 1; i <= n; i++) {
		nxt[i] = n + 1;
	}

	for (int i = 1; i <= n; i++) {
		while (scnt && a[stc[scnt - 1]] < a[i]) {
			scnt--;
		}
		if (scnt) {
			lxt[i] = stc[scnt - 1];
		}
		stc[scnt++] = i;
	}

	scnt = 0;
	for (int i = n; i >= 1; i--) {
		while (scnt && a[stc[scnt - 1]] <= a[i]) {
			scnt--;
		}
		if (scnt) {
			nxt[i] = stc[scnt - 1];
		}
		stc[scnt++] = i;
	}

	for (int i = 1; i <= n; i++) {
		val[i][0] = val2[i][0] = a[i];
	}

	for (int j = 1; j < 20; j++) {
		for (int i = 1; i <= n; i++) {
			int go = i + (1 << j) - 1;
			if (go > n) continue;
			val[i][j] = val[i][j - 1] | val[i + (1 << (j - 1))][j - 1];
		}
	}

	for (int j = 1; j < 20; j++) {
		for (int i = n; i >= 1; i--) {
			int go = i - (1 << j) + 1;
			if (go <= 0) continue;
			val2[i][j] = val2[i][j - 1] | val2[i - (1 << (j - 1))][j - 1];
		}
	}
}

int main() {
	freopen("data.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}

	init();

	long long res = 0;
	for (int i = 1; i <= n; i++) {
		int l = lxt[i], r = nxt[i];
		int l_len = i - l;
		int r_len = r - i;

		if (l_len < r_len) {
			int now_val = 0;
			for (int j = i; j >= l + 1; j--) {
				now_val |= a[j];
				int now = i;
				for (int k = 19; k >= 0 && now < r; k--) {
					if (now + (1 << k) - 1 < r && (now_val | val[now][k]) <= a[i]) {
						now_val = now_val | val[now][k];
						now = now + (1 << k);
					}
				}
				debug(i, j, now, r);
				res = res + r - now;
			}
		} else {
			int now_val = 0;
			for (int j = i; j < r; j++) {
				now_val |= a[j];
				int now = i;
				for (int k = 19; k >= 0 && now > l; k--) {
					if (now - (1 << k) + 1 > l && (now_val | val2[now][k]) <= a[i]) {
						now_val = now_val | val2[now][k];
						now = now - (1 << k);
					}
				}

				debug(i, j, now, l);
				res = res + now - l;
			}
		}
	}

	cout << res << endl;
	return 0;
}