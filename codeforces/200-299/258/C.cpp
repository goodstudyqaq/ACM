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

const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
int a[maxn];

int factor[maxn], fcnt;
void work(int val) {
	fcnt = 0;
	for (int i = 1; i * i <= val; i++) {
		if(val % i == 0) {
			factor[fcnt++] = i;
			if(i != val / i) {
				factor[fcnt++] = val / i;
			}
		}
	}
	sort(factor, factor + fcnt);
}


long long quick(long long a, long long b) {
	long long res = 1;
	while (b) {
		if (b % 2) res = res * a % mod;
		b /= 2;
		a = a * a % mod;
	}
	return res;
}

int main() {
	freopen("data.in", "r", stdin);
	int n;
	scanf("%d", &n);
	int mx = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		mx = max(mx, a[i]);
	}
	sort(a + 1, a + 1 + n);
	long long res = 0;
	for (int i = 1; i <= mx; i++) {
		work(i);
		int now_idx = 1;
		long long ans = 1;
		for (int j = 0; j < fcnt; j++) {
			int idx = lower_bound(a + now_idx, a + 1 + n, factor[j]) - a;
			ans = ans * quick(j, idx - now_idx) % mod;
			now_idx = idx;
		}
		ans = ans * (((quick(fcnt, n - now_idx + 1) - quick(fcnt - 1, n - now_idx + 1)) % mod + mod) % mod) % mod;
		res = (res + ans) % mod;
	}
	cout << res << endl;
}